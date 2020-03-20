#pragma once
#include <pthread.h>
#include <cstdlib>

class MutexLock
{
public:
    MutexLock() {
        pthread_mutex_init(&mutex,NULL);//default attr
    }

    int Lock()
    {
        return pthread_mutex_lock(&mutex);
    }

    int Unlock()
    {
        return pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_t * get_mutex()
    {
        return &mutex;
    }
    //non-virtual for efficiency
     ~MutexLock(){
        pthread_mutex_lock(&mutex);
        pthread_mutex_destroy(&mutex);
    }
private:
    pthread_mutex_t  mutex;
    
    //noncopyable
    MutexLock(const MutexLock &) = delete;
    MutexLock & operator=(const MutexLock & )=delete;
};


class MutexLockGuard{
//non-ctor and hold ref ,so must be construct with MutexLockGuard(MutexLock obj)
public:
    explicit MutexLockGuard(MutexLock &);
    void Lock()
    {
        mutexhold.Lock();
    }

    void Unlock()
    {
        mutexhold.Unlock();
    }
private:
    MutexLock & mutexhold;
};
