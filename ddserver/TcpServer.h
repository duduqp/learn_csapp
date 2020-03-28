#pragma once
#include "EventLoopThreadPool.h"
#include <memory>
class TcpServer
{
public:
    TcpServer() {}
    ~TcpServer() {}

private:
    EventLoop * masterloop;
    int numthread;
    bool started;
    short port;
    int listenfd;
    std::unique_ptr<EventLoopThreadPool> eventloopthreadpool;
    std::shared_ptr<Event> acceptor;
    static const int MAX_CONN=10000;
};

