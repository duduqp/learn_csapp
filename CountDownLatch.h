#pragma once
#include "ddserver/MutexLock_Util.h"
#include "ddserver/SyncCondition.h"
#include <pthread.h>


class CountDownLatch
{
public:
    explicit CountDownLatch(int count_):mutex(),cond(mutex),count(count_) {}
    ~CountDownLatch() {}
    void Wait();
    void DropOne();
private:
    MutexLock  mutex;
    SyncCondition cond;
    int count;
};

