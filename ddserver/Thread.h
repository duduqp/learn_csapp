#pragma once
#include <pthread.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <memory>
#include <unistd.h>
#include <functional>
#include "CountDownLatch.h"
#include "Uncopyable.h"
class Thread:public Uncopyable
{
public:
    typedef std::function<void()> ThreadFunc; 
    explicit Thread(const ThreadFunc &);
    ~Thread() ;
    
    void Start();
    int Join();

    pid_t Gettid() const{ return tid; }
    bool starting()const {
        return started;
    }

    bool joining() const{
        return joined;
    }
private:
    pthread_t ThreadId;
    pid_t tid;
    bool started;
    bool joined;
    ThreadFunc func;
    CountDownLatch latch;
};

