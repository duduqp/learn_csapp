#include <iostream>
#include "EventLoop.h"
#include <sys/eventfd.h>
#include "Event.h"
#include "Epoll.h"
#include <sys/epoll.h>
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

}
EventLoop:: ~EventLoop() {

}
void EventLoop::EventLoop::Loop(){

}
void EventLoop::Quit(){

}
void EventLoop::RunInLoop(){

}
void EventLoop::QueueInLoop(){

}
void EventLoop::AssertInLoopThread(){

}
void EventLoop::ShutDownEvent(std::shared_ptr<Event> event){

}
void EventLoop::AddToEpoll(std::shared_ptr<Event> event,int timeout_msecs)
{

}
void EventLoop::RemoveFromEpoll(std::shared_ptr<Event> event){

}
void EventLoop::UpdateEpoll(std::shared_ptr<Event> event,int timeout_msecs)
{

}



