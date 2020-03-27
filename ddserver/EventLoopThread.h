#pragma once
#include "Thread.h"
#include "MutexLock_Util.h"
#include "SyncCondition.h"
#include "EventLoop.h"

class EventLoopThread
{
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop * StartLoop();
private:
    bool exiting;
    //BO style -> OO style
    EventLoop * loop;
    Thread thread_;
    void threadfunc();
    MutexLock mutex;
    SyncCondition cond;
};

