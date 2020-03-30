#include <pthread.h>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include "RequestContent.h"
#include "EventLoop.h"
#include "Event.h"
#include "util.h"
#include "Logger.h"
using namespace std;

pthread_once_t MIME::once_ctl=PTHREAD_ONCE_INIT;
map<string,string>MIME::mime;

const uint32_t DEFAULT_EVENT_TYPE=EPOLLIN|EPOLLET|EPOLLONESHOT;
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

std::string MIME::GetMIME(const std::string &suffix) {
  pthread_once(&once_ctl, &MIME::init);
  if (mime.find(suffix) == mime.end())
    return mime["default"];
  else
    return mime[suffix];
}

char favicon[555] = {
    '\x89', 'P',    'N',    'G',    '\xD',  '\xA',  '\x1A', '\xA',  '\x0',
    '\x0',  '\x0',  '\xD',  'I',    'H',    'D',    'R',    '\x0',  '\x0',
    '\x0',  '\x10', '\x0',  '\x0',  '\x0',  '\x10', '\x8',  '\x6',  '\x0',
    '\x0',  '\x0',  '\x1F', '\xF3', '\xFF', 'a',    '\x0',  '\x0',  '\x0',
    '\x19', 't',    'E',    'X',    't',    'S',    'o',    'f',    't',
    'w',    'a',    'r',    'e',    '\x0',  'A',    'd',    'o',    'b',
    'e',    '\x20', 'I',    'm',    'a',    'g',    'e',    'R',    'e',
    'a',    'd',    'y',    'q',    '\xC9', 'e',    '\x3C', '\x0',  '\x0',
    '\x1',  '\xCD', 'I',    'D',    'A',    'T',    'x',    '\xDA', '\x94',
    '\x93', '9',    'H',    '\x3',  'A',    '\x14', '\x86', '\xFF', '\x5D',
    'b',    '\xA7', '\x4',  'R',    '\xC4', 'm',    '\x22', '\x1E', '\xA0',
    'F',    '\x24', '\x8',  '\x16', '\x16', 'v',    '\xA',  '6',    '\xBA',
    'J',    '\x9A', '\x80', '\x8',  'A',    '\xB4', 'q',    '\x85', 'X',
    '\x89', 'G',    '\xB0', 'I',    '\xA9', 'Q',    '\x24', '\xCD', '\xA6',
    '\x8',  '\xA4', 'H',    'c',    '\x91', 'B',    '\xB',  '\xAF', 'V',
    '\xC1', 'F',    '\xB4', '\x15', '\xCF', '\x22', 'X',    '\x98', '\xB',
    'T',    'H',    '\x8A', 'd',    '\x93', '\x8D', '\xFB', 'F',    'g',
    '\xC9', '\x1A', '\x14', '\x7D', '\xF0', 'f',    'v',    'f',    '\xDF',
    '\x7C', '\xEF', '\xE7', 'g',    'F',    '\xA8', '\xD5', 'j',    'H',
    '\x24', '\x12', '\x2A', '\x0',  '\x5',  '\xBF', 'G',    '\xD4', '\xEF',
    '\xF7', '\x2F', '6',    '\xEC', '\x12', '\x20', '\x1E', '\x8F', '\xD7',
    '\xAA', '\xD5', '\xEA', '\xAF', 'I',    '5',    'F',    '\xAA', 'T',
    '\x5F', '\x9F', '\x22', 'A',    '\x2A', '\x95', '\xA',  '\x83', '\xE5',
    'r',    '9',    'd',    '\xB3', 'Y',    '\x96', '\x99', 'L',    '\x6',
    '\xE9', 't',    '\x9A', '\x25', '\x85', '\x2C', '\xCB', 'T',    '\xA7',
    '\xC4', 'b',    '1',    '\xB5', '\x5E', '\x0',  '\x3',  'h',    '\x9A',
    '\xC6', '\x16', '\x82', '\x20', 'X',    'R',    '\x14', 'E',    '6',
    'S',    '\x94', '\xCB', 'e',    'x',    '\xBD', '\x5E', '\xAA', 'U',
    'T',    '\x23', 'L',    '\xC0', '\xE0', '\xE2', '\xC1', '\x8F', '\x0',
    '\x9E', '\xBC', '\x9',  'A',    '\x7C', '\x3E', '\x1F', '\x83', 'D',
    '\x22', '\x11', '\xD5', 'T',    '\x40', '\x3F', '8',    '\x80', 'w',
    '\xE5', '3',    '\x7',  '\xB8', '\x5C', '\x2E', 'H',    '\x92', '\x4',
    '\x87', '\xC3', '\x81', '\x40', '\x20', '\x40', 'g',    '\x98', '\xE9',
    '6',    '\x1A', '\xA6', 'g',    '\x15', '\x4',  '\xE3', '\xD7', '\xC8',
    '\xBD', '\x15', '\xE1', 'i',    '\xB7', 'C',    '\xAB', '\xEA', 'x',
    '\x2F', 'j',    'X',    '\x92', '\xBB', '\x18', '\x20', '\x9F', '\xCF',
    '3',    '\xC3', '\xB8', '\xE9', 'N',    '\xA7', '\xD3', 'l',    'J',
    '\x0',  'i',    '6',    '\x7C', '\x8E', '\xE1', '\xFE', 'V',    '\x84',
    '\xE7', '\x3C', '\x9F', 'r',    '\x2B', '\x3A', 'B',    '\x7B', '7',
    'f',    'w',    '\xAE', '\x8E', '\xE',  '\xF3', '\xBD', 'R',    '\xA9',
    'd',    '\x2',  'B',    '\xAF', '\x85', '2',    'f',    'F',    '\xBA',
    '\xC',  '\xD9', '\x9F', '\x1D', '\x9A', 'l',    '\x22', '\xE6', '\xC7',
    '\x3A', '\x2C', '\x80', '\xEF', '\xC1', '\x15', '\x90', '\x7',  '\x93',
    '\xA2', '\x28', '\xA0', 'S',    'j',    '\xB1', '\xB8', '\xDF', '\x29',
    '5',    'C',    '\xE',  '\x3F', 'X',    '\xFC', '\x98', '\xDA', 'y',
    'j',    'P',    '\x40', '\x0',  '\x87', '\xAE', '\x1B', '\x17', 'B',
    '\xB4', '\x3A', '\x3F', '\xBE', 'y',    '\xC7', '\xA',  '\x26', '\xB6',
    '\xEE', '\xD9', '\x9A', '\x60', '\x14', '\x93', '\xDB', '\x8F', '\xD',
    '\xA',  '\x2E', '\xE9', '\x23', '\x95', '\x29', 'X',    '\x0',  '\x27',
    '\xEB', 'n',    'V',    'p',    '\xBC', '\xD6', '\xCB', '\xD6', 'G',
    '\xAB', '\x3D', 'l',    '\x7D', '\xB8', '\xD2', '\xDD', '\xA0', '\x60',
    '\x83', '\xBA', '\xEF', '\x5F', '\xA4', '\xEA', '\xCC', '\x2',  'N',
    '\xAE', '\x5E', 'p',    '\x1A', '\xEC', '\xB3', '\x40', '9',    '\xAC',
    '\xFE', '\xF2', '\x91', '\x89', 'g',    '\x91', '\x85', '\x21', '\xA8',
    '\x87', '\xB7', 'X',    '\x7E', '\x7E', '\x85', '\xBB', '\xCD', 'N',
    'N',    'b',    't',    '\x40', '\xFA', '\x93', '\x89', '\xEC', '\x1E',
    '\xEC', '\x86', '\x2',  'H',    '\x26', '\x93', '\xD0', 'u',    '\x1D',
    '\x7F', '\x9',  '2',    '\x95', '\xBF', '\x1F', '\xDB', '\xD7', 'c',
    '\x8A', '\x1A', '\xF7', '\x5C', '\xC1', '\xFF', '\x22', 'J',    '\xC3',
    '\x87', '\x0',  '\x3',  '\x0',  'K',    '\xBB', '\xF8', '\xD6', '\x2A',
    'v',    '\x98', 'I',    '\x0',  '\x0',  '\x0',  '\x0',  'I',    'E',
    'N',    'D',    '\xAE', 'B',    '\x60', '\x82',
};


void RequestContent::Handle_Read(){
    std::cout << "RequestContent Handle_Read"<<std::endl;
    uint32_t & eventtype=event->GetEventType();
    std::cout << __func__<<std::endl;
    do{
        bool zero=false;
        int readnum=readn(fd,read_buffer,zero);
        LOG << "Request:"<<readnum;
        if(connection_state==CONNECTION_CLOSING)
        {
            read_buffer.clear();
            break;
        }

        if(zero)
        {
            //peer closed
            connection_state=CONNECTION_CLOSING;
            if(readnum==0) break;
        }else if(readnum<0)
        {
            LOG << "Bad Request" ;
            error_status=true;
            Handle_Error(fd,200,"Bad Request");
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
                Handle_Error(fd,400,"bad request");
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
        uint32_t & events=event->GetEventType();
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
    std::cout << __func__<<std::endl;
    DetachTimer();//guard operation
    uint32_t & events=event->GetEventType();
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
            eventloop->UpdateEpoll(event,timeout);
        }else if(keep_alive)
        {
            events |=(EPOLLIN|EPOLLET);
            int timeout=DEFAULT_KEEP_ALIVE_TIME;
            eventloop->UpdateEpoll(event,timeout);
        }else{
            //normally closed
            events|=(EPOLLIN|EPOLLET);
            int timeout=(DEFAULT_KEEP_ALIVE_TIME>>1);
            eventloop->UpdateEpoll(event,timeout);
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
    std::cout << __func__<<std::endl;
    string & str=read_buffer;
    string backup=str;
    //GET /index...HTTP1.0 \r\n
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
        str=str.substr(pos+1);//have more than this line
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
        http_method=HTTP_METHOD_HEAD;//HEAD TODO
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
    // GET /xxx?param1=value1&param2=value2 HTTP/1.1 \r\n  
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
    std::cout << __func__<<std::endl;
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

int RequestContent::Analysis_Req()
{
    std::cout << __func__<<std::endl;
    if (http_method == HTTP_METHOD_POST) {
        //TODO
    } else if (http_method == HTTP_METHOD_GET || http_method == HTTP_METHOD_HEAD) {
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
            Handle_Error(fd, 404, "Not Found!");
            return ANALYSIS_STATUS_ERROR;
        }
        header += "Content-Type: " + filetype + "\r\n";
        header += "Content-Length: " + to_string(sbuf.st_size) + "\r\n";
        header += "Server: DDServer\r\n";
        // 头部结束
        header += "\r\n";
        write_buffer += header;

        if (http_method==HTTP_METHOD_HEAD) return ANALYSIS_STATUS_SUCCESS;

        int src_fd = open(file_name.c_str(), O_RDONLY, 0);
        if (src_fd < 0) {
            write_buffer.clear();
            Handle_Error(fd, 404, "Not Found!");
            return ANALYSIS_STATUS_ERROR;
        }
        void *mmapRet = mmap(NULL, sbuf.st_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
        close(src_fd);
        if (mmapRet == (void *)-1) {
            munmap(mmapRet, sbuf.st_size);
            write_buffer.clear();
            Handle_Error(fd, 404, "Not Found!");
            return ANALYSIS_STATUS_ERROR;
        }
        char *src_addr = static_cast<char *>(mmapRet);
        write_buffer += string(src_addr, src_addr + sbuf.st_size);
        
        munmap(mmapRet, sbuf.st_size);
        return ANALYSIS_STATUS_SUCCESS;
    }
    return ANALYSIS_STATUS_ERROR;
}

void RequestContent::Handle_Error(int fd,int http_code,const std::string & msg)
{
    std::cout << __func__<<std::endl;
    std::string msg_=msg+" ";
    char send_buffer[MAX_BUF];
    std::string body,header;
    body+="<html><title>sorry ...oops</title>";

    //more
    header+="HTTP/1.1"+std::to_string(http_code)+msg_+"\r\n";
    header+="Content-Type: text/html\r\n";
    header+="Connection: Close\r\n";
    header+="Content-Length: "+std::to_string(body.size())+"\r\n";
    header+="DDSERVER\r\n\r\n";

    sprintf(send_buffer,"%s",header.c_str());
    writen(fd,send_buffer,sizeof(send_buffer));
    sprintf(send_buffer,"%s",body.c_str());
    writen(fd,send_buffer,sizeof(send_buffer));

}

void RequestContent::Handle_Close()
{
    connection_state=CONNECTION_CLOSING;
    std::shared_ptr<RequestContent> guard(shared_from_this());//secure this RC alive when next call use weak_ptr.lock()
    eventloop->RemoveFromEpoll(event);    
}

void RequestContent::Init_Event(){
    std::cout << __func__<<std::endl;
    event->SetEventType(DEFAULT_EVENT_TYPE);
    eventloop->AddToEpoll(event,DEFAULT_EXPIRED_TIME);
} 

void RequestContent::DetachTimer(){
  if (timer.lock()) {
    shared_ptr<TimeNode> my_timer(timer.lock());
    my_timer->ClearReq();
    timer.reset();
  }
}

void RequestContent::Reset(){
    std::cout << __func__<<std::endl;
    file_name.clear();
    path.clear();
    cursor = 0;
    analysis_state= PARSE_STATUS_URI;
    header_state = H_START;
    headers.clear();
    if (timer.lock()) {
        std::shared_ptr<TimeNode> my_timer(timer.lock());
        my_timer->ClearReq();
        timer.reset();
    }
}

RequestContent::RequestContent(EventLoop * baseloop,int fd_):eventloop(baseloop),
    fd(fd_),event(new Event(baseloop,fd_)),error_status(false),connection_state(CONNECTION_ON),
    http_method(HTTP_METHOD_GET),http_version(HTTP_VERSION_11),cursor(0),analysis_state(PARSE_STATUS_URI),
    header_state(H_START),finished(false),keep_alive(false)
{
    std::cout << __func__<<std::endl;
event->SetReadHandler(std::bind(&RequestContent::Handle_Read, this));
event->SetWriteHandler(std::bind(&RequestContent::Handle_Write, this));
event->SetConnectionHandler(std::bind(&RequestContent::Handle_Connection, this));
}



