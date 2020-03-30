#include <iostream>
#include "ThreadPool.h"
#include <assert.h>
#include <pthread.h>
int ThreadPool::Add(Task t)
{
    MutexLockGuard mutexguard(mutex);
    if(!running)
    {
        return TASK_ADD_ERROR;
    }
    
    while(static_cast<int>(tasks.size())>=max_task_num)
    {
        NotFull.Wait();
    }
    assert(tasks.size()<max_task_num);

    tasks.push_back(t);
    NotEmpty.Notify();
    return TASK_ADD_SUCCESS;
}

int ThreadPool::Start(){
    MutexLockGuard mutexguard(mutex);
    if(running)
    {
        //lock guard
        return THREADPOOL_START_ERROR;
    }//already start

    for(int i=0;i<worker_num;++i)
    {
        workers.push_back(0);
        pthread_create(&(workers[i]),NULL,ThreadPool_Routine,static_cast<void *>(this));
    }
    return THREADPOOL_START_SUCCESS;

}

int ThreadPool::Stop(){
    MutexLockGuard mutexguard(mutex);
    if(!running)
    {
       return THREADPOOL_STOP_ERROR; 
    }
    running=false;
    NotEmpty.NotifyAll();
    for(auto & thr:workers)
    {
        pthread_join(thr,NULL);
    }
}

void * ThreadPool::ThreadPool_Routine(void * args){
    ThreadPool * threadpool=static_cast<ThreadPool*>(args);
    threadpool->mutex.Lock();
    while(threadpool->tasks.empty()&&threadpool->running)
    {
        threadpool->NotEmpty.Wait();
    }
    Task t=threadpool->tasks.front();
    threadpool->tasks.pop_front();
    threadpool->NotFull.Notify();
    threadpool->mutex.Unlock();
    t.func(t.args);
}



