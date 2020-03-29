#include <iostream>
#include "Logger.h"
#include <functional>
#include <map>
#include <memory>
#include <list>
#include <cstring>
#include <time.h>
#include <stdio.h>
const char * LogLevel::ToString(LogLevel::Level level)
{
    switch(level){
#define XX(N) \
    case LogLevel::N: \
        return #N; \
        break;

        XX(INFO);
        XX(WARNING);
        XX(ERROR);
        XX(FATAL);
#undef  XX
    }
}
Logger::Logger( std::string name):m_name(name),m_level(LogLevel::DEBUG){
        m_logformatter.reset(new LogFormatter("%f%s%l%s%t%s%m"));
        //default m_appender has a stdout
        auto ret=LogAppender::ptr(new StdoutLoggerAppender);
        std::cout << "default stdout's formatter: "<<ret->GetFormatter()<<std::endl;
        std::cout<<"i will set in manually"<<std::endl;
        ret->SetFormatter(this->m_logformatter);
        m_appenders.push_back(ret);
    }


void Logger::SetAppender(LogAppender::ptr appender)
{
    //if passed in append has not been set fotmatter
    if(!appender->GetFormatter())
    {
        appender->SetFormatter(this->m_logformatter);
    }
    m_appenders.push_back(appender);
}

void Logger::RemoveAppender(LogAppender::ptr appender)
{
    for(auto it:m_appenders)
    {
        if(it==appender){
            m_appenders.remove(it);
            break;
        }
    }
}


void Logger::Log(LogLevel::Level level,LogEvent::ptr event)
{
    std::cout << "Logger Log" <<m_appenders.size()<<std::endl;
    if(level>=m_level)
    {
        auto ret=shared_from_this();
        for(auto &i:m_appenders)
        {
            std::cout << i <<std::endl;
            std::cout << __FILE__ << __LINE__ << std::endl;
            i->Log(ret,level,event);
        }
    }
}

void Logger::Debug(LogEvent::ptr event)
{
    Log(LogLevel::DEBUG,event);
}
void Logger::Info(LogEvent::ptr event)
{
    Log(LogLevel::INFO,event);
}
void Logger::Warning(LogEvent::ptr event)
{
    Log(LogLevel::WARNING,event);
}

void Logger::Error(LogEvent::ptr event)
{
    Log(LogLevel::ERROR,event);
    
}

void Logger::Fatal(LogEvent::ptr event)
{
    Log(LogLevel::FATAL,event);
}

LoggerManager::LoggerManager()
{
    Init();
}

Logger::ptr LoggerManager::GetDefaultLogger()
{
    return m_default_logger;
}

void LoggerManager::Init(){
    m_default_logger=std::make_shared<Logger>("dudu");
}

Logger::ptr LoggerManager::GetLogger(const std::string & name)
{
    if(m_loggers.count(name)==0)
    {
        std::cout << "No Such Logger ,I will give you a default"<<std::endl;
        return m_default_logger;
    }
    return m_loggers[name]; 
}





void FileLoggerAppender::Log(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event)
{
    if(m_level<=level)
    {
        m_fstream<<m_formatter->format(logger,level,event);
    }
}

bool FileLoggerAppender::ReOpen()
{
    if(m_fstream)
    {
        m_fstream.close();
    }
    m_fstream.open(m_filename);
    return !m_fstream;
}
void StdoutLoggerAppender::Log(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event)
{
    std::cout << __FILE__ << __LINE__ << std::endl;
    if(m_level<=level)
    {
        std::cout << __FILE__ << __LINE__ << std::endl;
        std::cout << m_formatter<<std::endl;
        std::cout << m_formatter->format(logger,level,event); 
    }
}


std::string LogFormatter::format(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event)
{
    std::cout <<this<<std::endl;
    std::cout << __FILE__ << __LINE__ << std::endl;
    std::stringstream ss;
    std::cout <<m_items.empty()<<std::endl;
    for(auto &i:m_items)
    {
        std::cout << __FILE__ << __LINE__ << std::endl;
        std::cout <<m_items.size()<<std::endl;
        std::cout << i << std::endl;
        i->format(ss,logger,level,event);
    }
    return ss.str();
}




//"%t(tid)%d(time)%m(content)%w(wall_time)%line"
void LogFormatter::init(){
    //str format type
    //parse pattern
    std::cout << formatter_mapping.size()<<std::endl;
    for(auto it=formatter_mapping.begin();it!=formatter_mapping.end();++it)
    {
        std::cout << it->first << "  "  << it->second << std::endl;
    }
    std::cout << __FILE__ << __LINE__ << std::endl;
    for(size_t i = 0;i<m_pattern.size();++i)
    {
        std::cout << m_pattern << std::endl;
        std::cout << __FILE__ << __LINE__ << std::endl;
        
        if(m_pattern[i]!='%')
        {
            std::cout << std::to_string(m_pattern[i])<<std::endl;
            m_items.push_back(formatter_mapping[std::string(1,m_pattern[i])]);
            std::cout << m_items.back()<<std::endl;
        }
    }
    
}


class ContentFormatter:public LogFormatter::ItemFormat
{
public:
    ContentFormatter(const std::string & c="default msg"):msg(c){  }
    virtual void format(std::ostream & os,std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) override{
        std::cout << __FILE__ << __LINE__ << std::endl;
        os<<event->GetContent();
    }
    void SetContent(const std::string msg_)
    {
        msg=msg_;
    }
private:
    std::string msg;
};
class LevelFormatter:public LogFormatter::ItemFormat
{
public:
    virtual void  format(std::ostream & os,std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) override{
        os<<LogLevel::ToString(level);
    }
};


class TimeFormatter:public LogFormatter::ItemFormat
{
public:
    explicit TimeFormatter(const std::string & timefmt="%Y:%m:%d %H:%M:%S"):time_format(timefmt){
        std::cout << __FILE__ << __LINE__ <<std::endl;
    }

    virtual void format(std::ostream & os,std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) override{
         char buffer[64];
         time_t rawtm=event->GetTime();
        struct tm * tmdetails=localtime(&rawtm);
        strftime(buffer,sizeof(buffer),this->time_format.c_str(),tmdetails);
        std::string outputtm(buffer,strlen(buffer));
        os<<outputtm;
    }
    void SetTimeFmt(const std::string & fmt)
    {
        time_format=fmt;
    }
private:
    std::string time_format;
};
class WallTimeFormatter:public LogFormatter::ItemFormat
{
public:
    virtual void format(std::ostream & os,std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) override{
        os<<event->GetWallTime();
    }

};
class FileFormatter:public LogFormatter::ItemFormat
{
public:
    virtual void format(std::ostream & os,std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) override{
        os<<event->GetFile();
    }
};
class ThreadIdFormatter:public LogFormatter::ItemFormat
{
public:
    virtual void format(std::ostream & os,std::shared_ptr<Logger> logger, LogLevel::Level level,LogEvent::ptr event) override{
        os<<event->GetThreadId();
    }
};
class LineFormatter:public LogFormatter::ItemFormat
{
public:
    virtual void format(std::ostream & os,std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) override{
        os<<event->GetLine();
    }
};
class TabFormatter:public LogFormatter::ItemFormat
{
public:
    virtual void format(std::ostream & os,std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) override{
        os<<"    ";
    }
};


std::map<std::string,LogFormatter::ItemFormat::ptr> LogFormatter::formatter_mapping={
#define XX(str,CLASS)  \
    {#str,std::shared_ptr<LogFormatter::ItemFormat>(new CLASS)}
    

    XX(s,TabFormatter),
    XX(m,ContentFormatter),
    XX(l,LineFormatter),
    XX(f,FileFormatter),
    XX(t,TimeFormatter),
    XX(e,WallTimeFormatter),
    XX(i,ThreadIdFormatter)
#undef XX
};

extern Logger::ptr dudulogger=LogMgr::GetInstanceSMT()->GetDefaultLogger();
