#pragma once
#include "Event.h"
#include "MutexLock_Util.h"
#include "Epoll.h"
#include "Thread.h"
#include "CurrentThread.h"
class EventLoop
{
public:
    typedef std::function<void()> Func;
    EventLoop();
    ~EventLoop();
    void Loop();
    void Quit();
    void RunInLoop();
    void QueueInLoop();
    void AssertInLoopThread();
    void ShutDownEvent(std::shared_ptr<Event> event);

    void AddToEpoll(std::shared_ptr<Event> event,int timeout_msecs);
    void RemoveFromEpoll(std::shared_ptr<Event> event);
    void UpdateEpoll(std::shared_ptr<Event> event,int timeout_msecs);

    bool BeInLoopThread() const { return loopthreadid==CurrentThread::tid(); }
    
private:
    bool looping;
    bool quit;
    bool handling;
    bool handling_pendingfunc;
    std::shared_ptr<Epoll> epoller;
    int wakeupfd;
    std::shared_ptr<Event> wakeupevent;
    std::vector<Func> pendingfunc;

    const pid_t loopthreadid;
    mutable MutexLock mutex;

    void wakeup();
    void dopendingfunc();
    void handleread();
    void handleconnection();

};

