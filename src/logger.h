#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <unistd.h>
#include <string>
#include <pthread.h>
#include <stdlib.h>
#include <memory>
#include "MutexLock_Util.h"
#include "blocking_queue.h"
enum Level{
    DEBUG, 
    WARNING, 
    ERROR
};

class MutexLock;
class Logger{

public:
    //singleton
    static std::shared_ptr<Logger> GetInstance(){
        static Logger singleton_logger;
        return std::shared_ptr<Logger>(&singleton_logger);
    }

    static void * flush_log_thread(void * args)
    {
        Logger::GetInstance()->async_write_log();
    }

    bool init(const char * file_name,int log_buffer_size=8192,
              int buffer_lines=50000,int queue_size=0);

    void write_log(Level level,const char * format,...);
    
    void flush(void);

private:
    Logger();//singleton
    virtual ~Logger();
    void * async_write_log()
    {
        std::string cur_log;
        while(log_queue->pop(cur_log))
        {
           log_mutex.lock();
           fputs(cur_log.c_str(),log_stream);
           log_mutex.unlock();
        }
    }

    std::string log_file_path;
    std::string log_file_name;
    std::string log_buffer;
    int max_log_buffer_size;
    int cur_log_buffer_size;
    bool is_sync;
    FILE * log_stream;

    //sync
    MutexLock log_mutex;
    //pthread_mutex_t * log_mutex;
    blocking_queue<std::string> * log_queue;

};

#endif
