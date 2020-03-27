#pragma once
#include "MutexLock_Util.h"
#include "SyncCondition.h"
#include "Uncopyable.h"
#include <pthread.h>


class CountDownLatch:public Uncopyable
{
public:
     CountDownLatch(int count_):mutex(),cond(mutex),count(count_) {}
    ~CountDownLatch() {}
    void Wait();
    void DropOne();
private:
    mutable MutexLock  mutex;
    SyncCondition cond;
    int count;
};

