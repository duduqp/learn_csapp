#include <iostream>
#include "EventLoopThread.h"
#include <assert.h>



EventLoopThread::EventLoopThread():exiting(false),loop(nullptr),
thread_(std::bind(&EventLoopThread::threadfunc,this)),mutex(),cond(mutex){

}
EventLoopThread::~EventLoopThread(){
    exiting=true;
    if(!loop)
    {
        loop->Quit();
        thread_.Join();//otherwise it will detach in its dtor
    }
}
EventLoop * EventLoopThread::StartLoop(){
    assert(!thread_.starting());
    thread_.Start();
    {
        MutexLockGuard mutexguard(mutex);
        while(!loop)
        {
            cond.Wait();
        }
        loop->Loop();
    }
    return loop;
}


void EventLoopThread::threadfunc(){
    EventLoop loop_;//stack scope obj
    {
        MutexLockGuard mutexguard(mutex);
        loop=&loop_;
        //notify
        cond.NotifyAll();
    }
    
    MutexLockGuard mutexguard(mutex);
    loop=NULL;

}
