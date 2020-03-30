#pragma once
#include <ctime>
#include "MutexLock_Util.h"
#include "Uncopyable.h"

class SyncCondition: Uncopyable
{
public:
    SyncCondition(MutexLock & m) :mutex_hold(m){ pthread_cond_init(&cond,NULL); }
    ~SyncCondition() {
        pthread_cond_destroy(&cond);
    }

    int Wait()
    {
        return pthread_cond_wait(&cond,mutex_hold.get_mutex());
    }

    int Notify()
    {
        return pthread_cond_signal(&cond);
    }

    int NotifyAll()
    {
        return pthread_cond_broadcast(&cond);
    }

    bool WaitUntil(int secs)
    {
        //return false if time out or error
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME,&ts);
        ts.tv_sec+=static_cast<time_t>(secs);
        int err_ret=pthread_cond_timedwait(&cond,mutex_hold.get_mutex(),&ts);
        return err_ret==0;
    }


private:
    //non-copyable
//    SyncCondition & operator=(const SyncCondition & )=delete ;
//  SyncCondition(const SyncCondition &)=delete ;

    //posix condition
    MutexLock & mutex_hold;
    pthread_cond_t cond;
};

