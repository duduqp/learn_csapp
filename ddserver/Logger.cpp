#include <iostream>
#include "Logger.h"
#include <functional>

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


void Logger::SetAppender(LogAppender::ptr appender)
{
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
    if(level>=m_level)
    {
        auto ret=shared_from_this();
        for(auto &i:m_appenders)
        {

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

void FileLoggerAppender::Log(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event)
{
    if(m_level<=level)
    {
        m_fstream<<m_formatter->format(logger,event);
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
    if(m_level<=level)
    {
        std::cout << m_formatter->format(logger,event); 
    }
}


std::string LogFormatter::format(std::shared_ptr<Logger> logger,LogEvent::ptr event)
{
    std::stringstream ss;
    for(auto &i:m_items)
    {
        i->format(ss,logger,event);
    }
    return ss.str();
}




//"%t(tid)%d(time)%m(content)%w(wall_time)%line"
void LogFormatter::init(){
    //str format type
    //parse pattern
    for(size_t i = 0;i<m_pattern.size();++i)
    {
        if(m_pattern[i]!='%')
        {
            m_items.push_back(formatter_mapping[std::to_string(m_pattern[i])]);
        }
    }
}


class ContentFormatter:public LogFormatter::ItemFormat
{
public:
    virtual std::string format(std::ostream & os,std::shared_ptr<Logger> logger,LogEvent::ptr event) override{

    }
};
class LevelFormatter:public LogFormatter::ItemFormat
{
public:
    virtual std::string format(std::ostream & os,std::shared_ptr<Logger> logger,LogEvent::ptr event) override{
        os<<logger->GetLevel();
    }
};


class TimeFormatter:public LogFormatter::ItemFormat
{
public:
    explicit TimeFormatter(const std::string & timefmt="%Y:%m:%d %H:%M:%S"):time_format(timefmt){}

    virtual std::string format(std::ostream & os,std::shared_ptr<Logger> logger,LogEvent::ptr event) override{
        os<<event->GetTime();
    }
private:
    std::string time_format;
};
class WallTimeFormatter:public LogFormatter::ItemFormat
{
public:
    virtual std::string format(std::ostream & os,std::shared_ptr<Logger> logger,LogEvent::ptr event) override{
        os<<event->GetWallTime();
    }

};
class FileFormatter:public LogFormatter::ItemFormat
{
public:
    virtual std::string format(std::ostream & os,std::shared_ptr<Logger> logger,LogEvent::ptr event) override{
        os<<event->GetFile();
    }
};
class ThreadIdFormatter:public LogFormatter::ItemFormat
{
public:
    virtual std::string format(std::ostream & os,std::shared_ptr<Logger> logger,LogEvent::ptr event) override{
        os<<event->GetThreadId();
    }
};
class LineFormatter:public LogFormatter::ItemFormat
{
public:
    virtual std::string format(std::ostream & os,std::shared_ptr<Logger> logger,LogEvent::ptr event) override{
        os<<event->GetLine();
    }
};

std::map<std::string,LogFormatter::ItemFormat::ptr> LogFormatter::formatter_mapping={
#define XX(str,CLASS)  \
    {#str,std::shared_ptr<LogFormatter::ItemFormat>(new CLASS)}


    XX(m,ContentFormatter),
    XX(l,LineFormatter),
    XX(f,FileFormatter),
    XX(t,TimeFormatter),
    XX(e,WallTimeFormatter),
    XX(i,ThreadIdFormatter)
#undef XX
};

