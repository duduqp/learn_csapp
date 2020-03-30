#pragma once
#include <string>
#include <map>
#include <sys/epoll.h>
#include <time.h>
#include <memory>
#include <unistd.h>

//const is better than enum for debugging
//state of parsing procedure
const int PARSE_STATUS_URI= 1 ;
const int PARSE_STATUS_HEADER= 2 ;
const int PARSE_STATUS_RECV_BODY= 3 ;
const int PARSE_STATUS_ANALYSIS= 4 ;
const int PARSE_STATUS_FINISH= 5 ;

//max buffer size of application level
//page size 4K for os-level opitimization
const int BUFFER_SIZE = 4096;
//try again for some cases(i.e. EAGAIN)
const int TRY_LIMIT = 100;

//status of thread when parsing uri
const int URI_STATUS_ERROR = -2;
const int URI_STATUS_AGAIN = -1;
const int URI_STATUS_SUCCESS = 0;


//status of thread when parsing header
const int HEADER_STATUS_ERROR = -2;
const int HEADER_STATUS_AGAIN = -1;
const int HEADER_STATUS_SUCCESS = 0;

//status of analysis body
const int ANALYSIS_STATUS_ERROR=-2;
const int ANALYSIS_STATUS_AGAIN=-1;
const int ANALYSIS_STATUS_SUCCESS= 0;

//method of http and http version
const int HTTP_METHOD_GET = 1;
const int HTTP_METHOD_POST = 2;
const int HTTP_METHOD_HEAD = 3;
const int HTTP_VERSION_10 = 1;
const int HTTP_VERSION_11 = 2;

//epoll wait time limit
const int EPOLL_WAIT_DURATION = 120 ; //120ms
const int PEERCLOSED= 0;



//connection state 
const int CONNECTION_ON=0;
const int CONNECTION_CLOSING=1;
const int CONNECTION_OFF=2;

class MIME{
public:
    static std::string GetMIME(const std::string & suffix);
     
private:
    static void init();
    static pthread_once_t once_ctl;
    static std::map<std::string,std::string> mime;
    //util tool class
    MIME();
    MIME(const MIME & );
};

//msg symbol
enum MSG_SYMBOL{
    H_START=0,
    H_KEY,
    H_COLON,
    H_SPACE_AFTER_COLON,
    H_VALUE,
    H_CR,
    H_LF,
    H_END_CR,
    H_END_LF
};



class Event;
class EventLoop;
class TimeNode;

class RequestContent:public std::enable_shared_from_this<RequestContent>//stl template characteristic
{
public:
    
    ~RequestContent() { close(fd); }
    RequestContent(EventLoop * eventloop_,int fd_);//parameter from right to left ,and we declare member by this order


    std::shared_ptr<Event> GetEvent(){
        return event;
    }
    void LinkTimer(std::shared_ptr<TimeNode> tm){ timer=tm; }
    void Reset();
    void DetachTimer();
    /*void Disable_RW();
    void Disable_R();
    void Disable_W();
    void Enable_RW();
    void Enable_R();
    void Enable_W();*/

    //handler
    void Handle_Read();
    void Handle_Write();
    void Handle_Error(int fd,int http_code,const std::string & appendinfo);
    void Handle_Connection();
    void Handle_Close();
    int  Getfd() const;
    bool Readable() const;
    bool Writable() const;
    

    int Parse_URI();
    int Parse_Header();
    int Analysis_Req();
    void Init_Event();


private:
    std::string path;
    int fd;
    //int epoll_base;//wrap in a EventLoop
    EventLoop * eventloop;
    std::shared_ptr<Event> event;

    std::string read_buffer;
    std::string write_buffer;
    bool error_status;
    //int epoll_event_type;//wrap in a Event

    int connection_state;
    int http_method;
    int http_version;
    std::string file_name;
    int cursor;
    int analysis_state;
    int header_state;
    bool finished;
    bool keep_alive;//http opt

    std::map<std::string,std::string> headers;
    //std::shared_ptr<TimeNode> timer;//cyclic reference ,weakptr
    std::weak_ptr<TimeNode> timer;

    //bool readable;
    //bool writeable;

};

