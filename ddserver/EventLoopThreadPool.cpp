#include "Uncopyable.h"
#include "EventLoopThreadPool.h"
#include <assert.h>
EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop, int numThreads)
    : baseloop(baseLoop), started(false), numthreads(numThreads), next_(0) {
  if (numThreads <= 0) {
    LOG << "numThreads_ <= 0";
    abort();
  }
  std::cout << "EventLoopThreadPool ctor ok"<<std::endl;
}

void EventLoopThreadPool::Start() {
  baseloop->AssertInLoopThread();
  started = true;
  std::cout << "EventLoopThreadPool Start"<<std::endl;

  std::cout <<"In E T p : has:"<<numthreads<<std::endl;
  for (int i = 0; i < numthreads; ++i) {
    std::shared_ptr<EventLoopThread> t(new EventLoopThread());
    threads.push_back(t);
    loops.push_back(t->StartLoop());
    std::cout << "EventLoopThreadPool start for i:"<<i<<std::endl;
  }
}

EventLoop *EventLoopThreadPool::GetNextLoop() {
  baseloop->AssertInLoopThread();
  assert(started);
  EventLoop *loop = baseloop;
  if (!loops.empty()) {
    loop = loops[next_];
    next_ = (next_ + 1) % numthreads;
  }
  return loop;
}
