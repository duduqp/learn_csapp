#pragma once
#include <vector>
#include "EventLoop.h"
#include "EventLoopThread.h"
#include "Logger.h"
#include "Uncopyable.h"


class EventLoopThreadPool: Uncopyable {
public:
    EventLoopThreadPool(EventLoop * baseloop_,int numthreads_);
    ~EventLoopThreadPool() {LOG<<"~EventLoopThreadPooL";}

    EventLoop * GetNextLoop();
    void Start();
private:
    bool started;
    EventLoop * baseloop;
    std::vector<std::shared_ptr<EventLoopThread> > threads;
    std::vector<EventLoop*> loops;
    int numthreads;
    int next_;
};

