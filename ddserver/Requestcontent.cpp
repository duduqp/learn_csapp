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
    int * eventtype=&event->GetEventType();
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
        int & events=event->GetEventType();
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



int RequestContent::Parse_Header(){
    string & str=read_buffer;
    int key_start = -1, key_end = -1, value_start = -1, value_end = -1;
    int now_read_line_begin = 0;
    bool notFinish = true;
    size_t i = 0;
    for (; i < str.size() && notFinish; ++i) {
        switch (header_state) {
        case H_START: {
                          if (str[i] == '\n' || str[i] == '\r') break;
                          header_state = H_KEY;
                          key_start = i;
                          now_read_line_begin = i;
                          break;

                      }
        case H_KEY: {
                        if (str[i] == ':') {
                            key_end = i;
                            if (key_end - key_start <= 0) return HEADER_STATUS_ERROR;
                            header_state = H_COLON;

                        } else if (str[i] == '\n' || str[i] == '\r')
                            return HEADER_STATUS_ERROR;
                        break;

                    }
        case H_COLON: {
                          if (str[i] == ' ') {
                              header_state = H_SPACE_AFTER_COLON;

                          } else
                              return HEADER_STATUS_ERROR;
                          break;

                      }
        case H_SPACE_AFTER_COLON: {
                                       header_state = H_VALUE;
                                       value_start = i;
                                       break;

                                   }
        case H_VALUE: {
                          if (str[i] == '\r') {
                              header_state = H_CR;
                              value_end = i;
                              if (value_end - value_start <= 0) return HEADER_STATUS_ERROR;

                          } else if (i - value_start > 255)
                              return HEADER_STATUS_ERROR;
                          break;

                      }
        case H_CR: {
                       if (str[i] == '\n') {
                           header_state = H_LF;
                           string key(str.begin() + key_start, str.begin() + key_end);
                           string value(str.begin() + value_start, str.begin() + value_end);
                           headers[key] = value;
                           now_read_line_begin = i;

                       } else
                           return HEADER_STATUS_ERROR;
                       break;

                   }
        case H_LF: {
                       if (str[i] == '\r') {
                           header_state = H_END_CR;

                       } else {
                           key_start = i;
                           header_state = H_KEY;

                       }
                       break;

                   }
        case H_END_CR: {
                           if (str[i] == '\n') {
                               header_state = H_END_LF;

                           } else
                               return HEADER_STATUS_ERROR;
                           break;

                       }
        case H_END_LF: {
                           notFinish = false;
                           key_start = i;
                           now_read_line_begin = i;
                           break;

                       }

        }

    }
    if (header_state == H_END_LF) {
        str = str.substr(i);
        return HEADER_STATUS_SUCCESS;

    }
    str = str.substr(now_read_line_begin);
    return  HEADER_STATUS_AGAIN;
}

void RequestContent::Analysis_Req()
{
    if (http_method == HTTP_METHOD_POST) {
        //TODO
    } else if (http_method == HTTP_METHOD_GET || http_method == HTTP_METHOD_GET) {
        string header;
        header += "HTTP/1.1 200 OK\r\n";
        if (headers.find("Connection") != headers.end() &&
            (headers["Connection"] == "Keep-Alive" ||
             headers["Connection"] == "keep-alive")) {
            keep_alive = true;
            header += string("Connection: Keep-Alive\r\n") + "Keep-Alive: timeout=" +
                to_string(DEFAULT_KEEP_ALIVE_TIME) + "\r\n";
        }
        int dot_pos = file_name.find('.');
        string filetype;
        if (dot_pos < 0)
            filetype = MIME::GetMIME("default");
        else
            filetype = MIME::GetMIME(file_name.substr(dot_pos));

        // echo test
        if (file_name == "hello") {
            write_buffer =
                "HTTP/1.1 200 OK\r\nContent-type: text/plain\r\n\r\nHello World";
            return ANALYSIS_STATUS_SUCCESS;
        }
        if (file_name == "favicon.ico") {
            header += "Content-Type: image/png\r\n";
            header += "Content-Length: " + to_string(sizeof favicon) + "\r\n";
            header += "Server: DD Server\r\n";

            header += "\r\n";
            write_buffer += header;
            write_buffer += string(favicon, favicon + sizeof favicon);
            ;
            return ANALYSIS_STATUS_SUCCESS;
        }

        struct stat sbuf;
        if (stat(file_name.c_str(), &sbuf) < 0) {
            header.clear();
            handleError(fd_, 404, "Not Found!");
            return ANALYSIS_STATUS_ERROR;
        }
        header += "Content-Type: " + filetype + "\r\n";
        header += "Content-Length: " + to_string(sbuf.st_size) + "\r\n";
        header += "Server: DDServer\r\n";
        // 头部结束
        header += "\r\n";
        write_buffer += header;

        if (method_ == METHOD_HEAD) return ANALYSIS_STATUS_SUCCESS;

        int src_fd = open(file_name.c_str(), O_RDONLY, 0);
        if (src_fd < 0) {
            write_buffer.clear();
            handleError(fd_, 404, "Not Found!");
            return ANALYSIS_STATUS_ERROR;
        }
        void *mmapRet = mmap(NULL, sbuf.st_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
        close(src_fd);
        if (mmapRet == (void *)-1) {
            munmap(mmapRet, sbuf.st_size);
            write_buffer.clear();
            handleError(fd, 404, "Not Found!");
            return ANALYSIS_STATUS_ERROR;
        }
        char *src_addr = static_cast<char *>(mmapRet);
        write_buffer += string(src_addr, src_addr + sbuf.st_size);
        
        munmap(mmapRet, sbuf.st_size);
        return ANALYSIS_STATUS_SUCCESS;
    }
}










