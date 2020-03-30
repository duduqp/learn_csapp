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
#include "util.h"

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
        if(t_currentthreadloop==nullptr)
        {
            t_currentthreadloop=this;
        }

        std::cout <<"EventlOOP cTOR"<<std::endl;
        //init wakeupevent
        wakeupevent->SetEventType(EPOLLIN|EPOLLET);
        wakeupevent->SetReadHandler(std::bind(&EventLoop::handleread,this));
        wakeupevent->SetConnectionHandler(std::bind(&EventLoop::handleconnection,this));

        //add to epoller
        std::cout << "eventloop wakeupfd :"<<wakeupfd<<std::endl; 
        epoller->Epoll_Add(wakeupevent,0);
//        std::cout<< "epoller base?"<<epoller->GetEpollBase()<<std::endl;
}
EventLoop:: ~EventLoop() {
    //note : i ignore the rest funcs in pending
    close(wakeupfd);
    t_currentthreadloop=nullptr;
}
void EventLoop::Loop(){
    std::cout << "Event LOOP START LOOP"<<std::endl;
    assert(!looping);
    assert(BeInLoopThread());
    looping=true;
    quit=false;
    std::vector<std::shared_ptr<Event>> ret;
    std::cout << "EventLoop will start loop"<<std::endl;

    while(!quit)
    {
        ret.clear();
        ret=epoller->Poll();
        std::cout << "eventloop loop returned from epoller poll"<<ret.size()<<std::endl;
        //begin processing events returned from io multplexing
        handling=true;
        std::cout <<"epoller poll() return "<<ret.size()<<std::endl;
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
void EventLoop::Quit(){
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
void EventLoop::RunInLoop(Func &&func){
    if(BeInLoopThread())
    {
        std::cout << "eventloop runinloop()"<<std::endl;
        func();
    }else{
        std::cout << "eventloop queueinloop()"<<std::endl;
        QueueInLoop(std::move(func));//append to the async queue 
    }
}
void EventLoop::QueueInLoop(Func &&func){
    std::cout <<" eventloop queueinloop"<<std::endl;
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
void EventLoop::AssertInLoopThread(){
    assert(BeInLoopThread());
}
void EventLoop::ShutDownEvent(std::shared_ptr<Event> event){
//todo in util.h
  //  ShutDownWR(event->Getfd());
}
void EventLoop::AddToEpoll(std::shared_ptr<Event> event,int timeout_msecs)
{
    std::cout << epoller->GetEpollBase()<<std::endl;
    std::cout << "eventloop addtoepoll"<<std::endl;
    epoller->Epoll_Add(event,timeout_msecs);
}
void EventLoop::RemoveFromEpoll(std::shared_ptr<Event> event){
    epoller->Epoll_Delete(event);
}
void EventLoop::UpdateEpoll(std::shared_ptr<Event> event,int timeout_msecs)
{
    epoller->Epoll_Mod(event,timeout_msecs);
}
void EventLoop::wakeup(){
 uint64_t one=1;
 ssize_t ret=writen(wakeupfd,&one,sizeof(one));
 if(ret!=sizeof(one))
 {
     LOG<<"wakeup error";
 }
}
void EventLoop::dopendingfunc(){
    std::vector<Func> funcs;
    handling_pendingfunc=true;
    {
        MutexLockGuard guard(mutex);
        funcs.swap(pendingfunc);
    }

    for(auto & f:funcs) f();

    handling_pendingfunc=false;
}
void EventLoop::handleread(){
    uint64_t one=1;
    ssize_t ret=readn(wakeupfd,&one,sizeof(one));
    if(ret!=sizeof(one))
    {
        LOG<<"read wakeupevent error";
    }
    wakeupevent->SetEventType(EPOLLIN|EPOLLET);
}
void EventLoop::handleconnection(){
    UpdateEpoll(wakeupevent,0);
}


