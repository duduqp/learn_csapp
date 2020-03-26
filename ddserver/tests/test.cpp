#include <iostream>
#include "../Logger.h"
#include <time.h>
using namespace std;
int main()
{
    Logger::ptr ddlog=std::shared_ptr<Logger>(new Logger("ddlog"));
    ddlog->SetAppender(LogAppender::ptr(new StdoutLoggerAppender));
    LogEvent::ptr eventptr(new LogEvent(__FILE__,__LINE__,0,1,time(0),"hello")); 
    ddlog->Log(LogLevel::DEBUG,eventptr);
    //std::cout << "Hello world" << std::endl;
    return 0;
}


