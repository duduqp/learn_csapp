#include <pthread.h>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include "RequestContent.h"
#include "EventLoop.h"
#include "Event.h"
#include "util.h"
using namespace std;

pthread_once_t MIME::once_ctl=PTHREAD_ONCE_INIT;
map<string,string>MIME::mime;

const int DEFAULT_EVENT_TYPE=EPOLLIN|EPOLLET;
const int DEFAULT_EXPIRED_TIME=2000;//ms
const int DEFAULT_KEEP_ALIVE_TIME=5*60*1000;//5min

void MIME::init(){
    mime[".html"]="text/html";
    mime[".avi"]="video/x-msvideo";
    mime[".bmp"]="image/bmp";
    mime[".c"]="text/plain";
    mime[".doc"]="application/msword";
    mime[".gif"]="image/gif";
    mime[".gz"]="application/x-gzip";
    mime[".htm"]="text/html";
    mime[".ico"]="image/x-icon";
    mime[".jpg"]="image/jpeg";
    mime[".png"]="image/png";
    mime[".txt"]="text/plain";
    mime[".mp3"]="audio/mp3";
    mime["default"]="text/html";
}


void RequestContent::Handle_Read(){
    int * eventtype=event->GetEvent();
    do{
        int readnum=readn(fd,read_buffer);
        LOG << "Request:"<<read_buffer;
        if(connection_state==CONNECTION_CLOSING)
        {
            read_buffer.clear();
            break;
        }

        if(readnum==PEER_CLOSED)
        {
            //peer closed
            connection_state=CONNECTION_CLOSING;
        }else if(readnum<0)
        {
            LOG << "Bad Request" ;
            error_status=true;
            Handle_Error();
            break;
        }

        if(analysis_state==PARSE_STATUS_URI)
        {
            int ret=Parse_URI();
            if(ret==URI_STATUS_AGAIN)
            {
                break;
            }else if(ret==URI_STATUS_ERROR)
            {
                LOG <<"fd: "<<fd<< " URI#|"<<read_buffer <<"|#";
                read_buffer.clear();
                error_status=true;
                Handle_Error(fd,400,"Bad Request");
                break;
            }else{
                analysis_state=PARSE_STATUS_HEADER;//next go to parse header
            } 
        }
        if(analysis_state==PARSE_STATUS_HEADER)
        {
            int ret=Parse_Header();
            if(ret==HEADER_STATUS_AGAIN)
            {
                break;//since analysis state has not been changed
            }else if(ret==HEADER_STATUS_ERROR)
            {
                LOG << "fd: "<<fd <<"HEADER#";
                error_status=true;
                break;
            }
            //!post todo
            analysis_state=PARSE_STATUS_ANALYSIS;
            
        }
        if(analysis_state==PARSE_STATUS_ANALYSIS)
        {
            int ret=Analysis_Req();
            if(ret==ANALYSIS_STATUS_SUCCESS)
            {
                analysis_state=PARSE_STATUS_FINISH;
                break;
            }else{
                //ERROR
                error_status=true;
                break;
            }
        }
    }while(0);//end while
    //check error_status
    //no error
    if(!error_status)
    {
        if(!write_buffer.empty())
        {
            Handle_Write();
        }
        //HandleWrite correct(no error)
        if(!error_status&&analysis_state==PARSE_STATUS_FINISH)
        {
            Reset();//finished read and write 
            if(!read_buffer.empty())
            {
                if(connection_state!=CONNECTION_CLOSING)
                {
                    Handle_Read();//again
                }
            }
        }else if(!error_status&&connection_state!=CONNECTION_OFF)
        {
            eventtype|=EPOLLIN;
        }
    }
}


void RequestContent::Handle_Write(){
    if(!error_status&&connection_state!=CONNECTION_OFF)
    {
        int & events=event->GetEvent();
        if(writen(fd,write_buffer)<0)
        {
            LOG << "fd :" <<fd <<"WRITE#";
            events=0;
            error_status=true;      
        }
        if(!write_buffer.empty())
        {
            events|=EPOLLOUT;//application level not finish (writen will clear the writebuffer)
            //note this app based on ET-MODE
            //if we can write out whole buffer,we need to listen peer buffer status whether writable
        }
    }
}

void RequestContent::Handle_Connection(){
    DetachTimer();//guard operation
    int & events=event->GetEvent();
    if(!error_status&&connection_state==CONNECTION_ON)
    {
        if(events!=0)
        {
            int timeout=DEFAULT_EXPIRED_TIME;
            if(keep_alive) timeout=DEFAULT_KEEP_ALIVE_TIME;
            if((events & EPOLLIN)&&(events&EPOLLOUT)){
                events=0;
                events|=EPOLLOUT;
            }

            events|=EPOLLET;//set epoll edge trigger 
            eventloop->UpdatePoller(event,timeout);
        }else if(keep_alive)
        {
            events |=(EPOLLIN|EPOLLET);
            int timeout=DEFAULT_KEEP_ALIVE_TIME;
            event->UpdatePoller(event,timeout);
        }else{
            //normally closed
            events|=(EPOLLIN|EPOLLET);
            int timeout=(DEFAULT_KEEP_ALIVE_TIME>>1);
            event->UpdatePoller(event,timeout);
        }
    }//end if
    else if(!error_status&&connection_state==CONNECTION_CLOSING
            &&(events & EPOLLOUT)){
            events=(EPOLLOUT|EPOLLET); 
    }else{
        eventloop->RunInLoop(std::bind(&RequestContent::Handle_Close,shared_from_this()));
    }
}


int RequestContent::Parse_URI(){
    string & str=read_buffer;
    string backup=str;
    //GET /index...HTTP1.0 /r/n
    size_t pos=str.find('\r',cursor);
    if(pos==std::string::npos)
    {
        //not find?
        return URI_STATUS_AGAIN;
    }
    //"cut" the request line from readbuffer(for space efficiency)
    string requestline=str.substr(0,pos);//exclude "\r\n"
    if(str.size()>pos+1)
    {
        str=str.substr(pos+2);//have more than this line
    }else{
        str.clear();
    }
    //Method
    int posGet=-1,posHead=-1,posPost=-1;//post todo
    posGet=requestline.find("GET");
    posHead=requestline.find("HEAD");
    posPost=requestline.find("POST");

    if(posGet>=0)//get
    {
        pos=posGet;
        http_method=HTTP_METHOD_GET;
    }else if(posHead>=0)
    {
        pos=posHead;
        http_method=HTTP_METHOD_HEAD;
    }else if(posPost>=0){
        pos=posPost;
        http_method=HTTP_METHOD_POST;
    }else{
        //error
        return URI_STATUS_ERROR;
    }

    
    //uri  (i.e) /index.html
    pos=requestline.find("/",pos);
    if(pos<0)//"/"only
    {
        file_name="index.html";//prepared static web-page(welcome page)
        http_version=HTTP_VERSION_11;
        return URI_STATUS_SUCCESS;
    }else{
        //note that between uri and httpversion there is a space ' '
        size_t space_pos=requestline.find(' ',pos);
        if(space_pos==std::string::npos)
        {
            return URI_STATUS_ERROR;
        }else{
            if(space_pos>pos+1)
            {
                // i.e "...    [ / ]xxx[        ]"
                //              pos      spacepos
                file_name=requestline.substr(pos+1,space_pos-pos-1);
                size_t posparam=file_name.find("?");
                if(posparam>=0)
                {
                   // "i.e      /xxxxxxx?param1=value1 ..."
                    file_name=file_name.substr(0,posparam);
                }
            }else{
                file_name="index.html";
            }
        }
        pos=space_pos;//begin from first space
    }  
    
    //httpversion
    // GET /xxx?param1=value1&param2=value2 HTTP/1.1 /r/n  
    pos=requestline.find("/",pos);
    if(pos==std::string::npos)
    {
        return URI_STATUS_ERROR;
    }else{
        if(requestline.size()-pos<=3)
        {
            return URI_STATUS_ERROR;
        }else{
            string HTTP_version=requestline.substr(pos+1,3);
            if(HTTP_version=="1.0")
            {
                http_version=HTTP_VERSION_10;
            }else if(HTTP_version=="1.1")
            {
                http_version=HTTP_VERSION_11;
            }else{
                return URI_STATUS_ERROR;
            }
        }
    }
    return URI_STATUS_SUCCESS;

}

















