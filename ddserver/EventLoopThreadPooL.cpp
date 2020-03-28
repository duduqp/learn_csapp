#include "EventLoopThreadPooL.h"
#include "Logger.h"
EventLoopThreadPooL::EventLoopThreadPooL(EventLoop * base,int num):
    baseloop(base),numthreads(num){
        if(numthreads<=0)
        {
            LOG<<"EventLoopThreadPooL Error : numthread invalid";
            abort();
        }
    }


void EventLoopThreadPooL::Start()
{
    baseloop->AssertInLoopThread();
    started=true;
    for(int i=0;i<numthreads;++i)
    {
        std::shared_ptr<EventLoopThread> t(make_shared(EventLoopThread()));
        threads.push_back(t);
        loops.push_back(t->StartLoop());
    }
}

EventLoop * GetNextLoop()
{
    baseloop->AssertInLoopThread();
    assert(started);
    EventLoop * loop;
    if(!loops.empty())
    {
        loop=loops[next_];
        next_=(next_+1)%numthreads;
    }
    return loop;
}
