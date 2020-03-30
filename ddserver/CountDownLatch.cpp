#include "MutexLock_Util.h"
#include "CountDownLatch.h"
#include "Uncopyable.h"
#include "SyncCondition.h"

void CountDownLatch::Wait(){
    MutexLockGuard guard(mutex);
    while(count>0)
    {
        cond.Wait();
    }
}

void CountDownLatch::DropOne(){
    MutexLockGuard guard(mutex);
    count--;
    if(count==0)
    {
        cond.NotifyAll();
    }
}



