#pragma once
#include <string>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include "Singleton.h"
class StdoutLoggerAppender;
class LogAppender;
class Logger;
class LoggerManager;
class LogFormatter;
typedef Singleton<LoggerManager> LogMgr;
class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(const char * file,uint32_t line,uint32_t walltime
            , uint32_t ThreadId,uint64_t tm,std::string msg="default msg"):
        m_file(file),m_line(line),m_walltime(walltime),m_threadid(ThreadId),m_time(tm)
        ,m_content(msg){}

    const char * GetFile() const{ return m_file; }

    uint32_t GetLine() const{ return m_line; }
    uint32_t GetWallTime() const{ return m_walltime; }
    uint32_t GetThreadId() const{ return m_threadid; }
    uint32_t GetTime() const{ return m_time; }
    std::string GetContent() const{ return m_content; }
private:
    const char * m_file=nullptr;
    uint32_t m_line=0;
    uint32_t m_walltime; 
    uint32_t m_threadid=0;
    std::string m_content;
    uint64_t m_time;
};



class LogLevel{
public:
 enum Level{
        DEBUG=1,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };
 static const char * ToString(LogLevel::Level level) ;
};

class LogFormatter{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string & pattern):m_pattern(pattern){ init(); }//must init!
    std::string format(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event);
public:
    class ItemFormat{
    public:
        typedef std::shared_ptr<ItemFormat> ptr;
        virtual ~ItemFormat(){}
        virtual void format(std::ostream & os,std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event)=0;
    };
private:
    static std::map<std::string,ItemFormat::ptr> formatter_mapping;
    std::string m_pattern;
    std::vector<ItemFormat::ptr> m_items;
    void init();
};

class LogAppender
{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual void Log(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr logEvent)=0;
    virtual ~LogAppender(){};

    void SetFormatter(LogFormatter::ptr formatter)
    {
        m_formatter=formatter;
    }

    LogFormatter::ptr GetFormatter()const{ return m_formatter; }

protected:
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
};

class Logger:public std::enable_shared_from_this<Logger>
{
public:
    typedef std::shared_ptr<Logger> ptr;

    void Log(LogLevel::Level level,LogEvent::ptr  event);
    Logger( std::string name);
    ~Logger() {}

    void Debug(LogEvent::ptr event);
    void Info(LogEvent::ptr event);
    void Warning(LogEvent::ptr event);
    void Error(LogEvent::ptr event);
    void Fatal(LogEvent::ptr event);

    void SetAppender(LogAppender::ptr appender);
    void RemoveAppender(LogAppender::ptr appender);
    LogLevel::Level  GetLevel() const
    {
        return m_level;
    }
    void SetLogLevel(LogLevel::Level level)
    {
        m_level=level;
    }

    const std::string GetName() const{return m_name;}


private:
    std::string m_name;
    LogLevel::Level m_level;
    std::list<LogAppender::ptr> m_appenders;
    LogFormatter::ptr m_logformatter;

};


class LoggerManager{
    public:
        LoggerManager();
        Logger::ptr GetLogger(const std::string & loggername);
        Logger::ptr GetDefaultLogger();
    private:
        std::map<std::string,Logger::ptr> m_loggers;
        void Init();
        Logger::ptr m_default_logger;
};





class StdoutLoggerAppender:public LogAppender{
public:
    typedef std::shared_ptr<StdoutLoggerAppender> ptr;
    virtual void Log(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) override;
    
private:
    
};

class FileLoggerAppender:public LogAppender{
public:
    typedef std::shared_ptr<StdoutLoggerAppender> ptr;
    explicit FileLoggerAppender(const std::string & filename):m_filename(filename){}
    virtual void Log(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) override;
    
    bool ReOpen();

private:
    std::string m_filename;
    std::ofstream m_fstream;
    
};









