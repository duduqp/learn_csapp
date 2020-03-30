#pragma once
#include "EventLoopThreadPool.h"
#include <memory>
class TcpServer
{
public:
    TcpServer(EventLoop * masterloop_,int numthreads_,short port_);
    ~TcpServer() {}
    EventLoop *getLoop() const { return masterloop; }
    void Start();
    void HandleNewConn();
    void HandleCurrentConn() {
    std::cout << "TcpSERVER handle new conn"<<std::endl;
    masterloop->UpdateEpoll(acceptor); }
private:
    EventLoop * masterloop;
    int numthreads;
    bool started;
    short port;
    int listenfd;
    std::unique_ptr<EventLoopThreadPool> eventloopthreadpool;
    std::shared_ptr<Event> acceptor;
    static const int MAX_CONN=10000;
};

