#pragma once
#include <functional>
#include <string>
#include <pthread.h>
#include "CountDownLatch.h"
class Thread
{
    typedef std::function<void()> ThreadFunc;
public:
    explicit Thread(const ThreadFunc & ,const std::string & threadname=std::string());
    ~Thread() {}
    void Start();
    int Join();
    bool Started() const{ return started; }
    pid_t GetTid() const{ return tid;     }
    const std::string & GetName() const { return name; }
private:
    void SetDefaultName();
    bool started;
    pthread_t pthread_id;
    pid_t tid;
    ThreadFunc func;
    std::string name;
    CountDownLatch latch;
    Thread(const Thread & ) = delete;
    Thread & operator=(const Thread &)=delete;
};

