#pragma once
#include <string>
#include <map>
#include <sys/epoll.h>
#include <time.h>



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
const int HTTP_VERSION_10 = 1;
const int HTTP_VERSION_11 = 2;

//epoll wait time limit
const int EPOLL_WAIT_DURATION = 120 ; //120ms

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






class requestcontent
{
public:
    requestcontent() {}
    ~requestcontent() {}

private:

};

