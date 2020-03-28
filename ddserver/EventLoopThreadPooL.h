#pragma once
#include <vector>
#include "EventLoop.h"
#include  "EventLoopThread.h"
#include "Logger.h"
#include "Uncopyable.h"
class EventLoopThreadPooL:public Uncopyable 
{
public:
    EventLoopThreadPooL(EventLoop * baseloop_,int numthreads_):baseloop(baseloop_),numthreads(numthreads_){}
    ~EventLoopThreadPooL() {LOG<<"~EventLoopThreadPooL";}

    EventLoop * GetNextLoop();
    void Start();
private:
    bool started;
    EventLoop * baseloop;
    std::vector<std::shared_ptr<EventLoopThread>> threads;
    std::vector<EventLoop*> loops;
    int numthreads;
    int next_;

};
