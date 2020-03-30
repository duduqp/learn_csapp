#include "MutexLock_Util.h"
#include "CountDownLatch.h"
#include "Uncopyable.h"
#include "SyncCondition.h"

void CountDownLatch::Wait(){
    mutex.Lock();
    while(count>0)
    {
        cond.Wait();
    }
}

void CountDownLatch::DropOne(){
    mutex.Lock();
    count--;
    if(count==0)
    {
        cond.NotifyAll();
    }
}



