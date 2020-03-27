#include <iostream>
#include "EventLoop.h"
#include <sys/eventfd.h>
#include <sys/epoll.h>
#include <assert.h>
#include <functional>
#include "Event.h"
#include "Epoll.h"
#include "Logger.h"
#include "MutexLock_Util.h"


__thread EventLoop * t_currentthreadloop=nullptr;
int eventfdinit(){
    int evtfd=eventfd(0,EFD_NONBLOCK|EFD_CLOEXEC);
    if(evtfd<0)
    {
        LOG << "eventfd error";
    }
    return evtfd;
}

EventLoop::EventLoop():looping(false),quit(false),
                        handling(false),handling_pendingfunc(false),
                        epoller(new Epoll()),wakeupfd(eventfdinit()),
                        wakeupevent(new Event(this,wakeupfd)),loopthreadid(CurrentThread::tid())
{
        assert(t_currentthreadloop==nullptr);
        t_currentthreadloop=this;
    
        //init wakeupevent
        wakeupevent->SetEventType(EPOLLIN|EPOLLET);
        wakeupevent->SetReadHandler(std::bind(&EventLoop::handleread,this));
        wakeupevent->SetConnectionHandler(std::bind(&EventLoop::handleconnection,this));

        //add to epoller
        epoller->Epoll_Add(wakeupevent,0);
}
EventLoop:: ~EventLoop() {
    //note : i ignore the rest funcs in pending
    close(wakeupfd);
    t_currentthreadloop=nullptr;
}
void EventLoop::EventLoop::EventLoop::Loop(){
    assert(!looping);
    assert(BeInLoopThread());
    looping=true;
    quit=false;
    std::vector<std::shared_ptr<Event>> ret;
    while(!quit)
    {
        ret.clear();
        ret=epoller->Poll();
        //begin processing events returned from io multplexing
        handling=true;
        for(auto & it:ret)
        {
            it->HandleEvent();
        }
        handling=false;
        //if some funcs are append asynchorouslly into pending funcs
        dopendingfunc();//some racing may happen
        epoller->HandleExpired();
    }
    looping=false;//but not quit yet
}
void EventLoop::EventLoop::Quit(){
    quit=true;
    //async quit;
    //we should wakeup to ensure primal thread can 
    ///return from epoller poll
    //and we never miss the funcs appended
    if(!BeInLoopThread())
    {
        wakeup();
    }
}
void EventLoop::EventLoop::RunInLoop(Func func){
    if(BeInLoopThread())
    {
        func();
    }else{
        QueueInLoop(func);//append to the async queue 
    }
}
void EventLoop::EventLoop::QueueInLoop(Func func){
    {
        MutexLockGuard mutexguard(mutex);
        pendingfunc.emplace_back(func);
    }
    //case 1 : another thread(async )
    //case 2 : local thread is dopendingfunc
    if(!BeInLoopThread()||handling_pendingfunc)
    {
        wakeup();
    }
}
void EventLoop::EventLoop::AssertInLoopThread(){
    assert(BeInLoopThread());
}
void EventLoop::EventLoop::ShutDownEvent(std::shared_ptr<Event> event){
//todo in util.h
  //  ShutDownWR(event->Getfd());
}
void EventLoop::EventLoop::AddToEpoll(std::shared_ptr<Event> event,int timeout_msecs)
{
    epoller->Epoll_Add(event,timeout_msecs);
}
void EventLoop::EventLoop::RemoveFromEpoll(std::shared_ptr<Event> event){
    epoller->Epoll_Delete(event);
}
void EventLoop::EventLoop::UpdateEpoll(std::shared_ptr<Event> event,int timeout_msecs)
{
    epoller->Epoll_Mod(event,timeout_msecs);
}
void EventLoop::wakeup(){
 uint64_t one=1;
 ssize_t ret=write(wakeupfd,&one,sizeof(one));
 if(ret!=sizeof(one))
 {
     LOG<<"wakeup error";
 }
}
void EventLoop::dopendingfunc(){

}
void EventLoop::handleread(){
    uint64_t one=1;
    ssize_t ret=read(wakeupfd,&one,sizeof(one));
    if(ret!=sizeof(one))
    {
        LOG<<"read wakeupevent error";
    }
    wakeupevent->SetEventType(EPOLLIN|EPOLLET);
}
void EventLoop::handleconnection(){
    UpdateEpoll(wakeupevent,0);
}


