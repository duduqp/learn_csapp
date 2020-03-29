#include <iostream>
#include "../Logger.h"
//#include "../Singleton.h"
#include <time.h>
using namespace std;
int main()
{
    //std::cout << "Hello world" << std::endl;
    //Logger::ptr ddlog=std::shared_ptr<Logger>(new Logger("ddlog"));
    //ddlog->SetAppender(LogAppender::ptr(new StdoutLoggerAppender));
   // LogEvent::ptr eventptr(new LogEvent(__FILE__,__LINE__,0,1,time(0),"hello")); 
   // ddlog->Log(LogLevel::DEBUG,eventptr);
 //  Logger::ptr dudulogger = LogMgr::GetInstanceSMT()->GetDefaultLogger();
   // LogEvent::ptr eventptr(new LogEvent(__FILE__,__LINE__,0,1,time(0),"DUDU HELLO"));
   // dudulogger->Log(LogLevel::DEBUG,eventptr);
    
    LOG("HELLO");
    std::cout << std::endl;
    return 0;
}


