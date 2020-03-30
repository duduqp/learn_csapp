#include "TcpServer.h"
#include "util.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include "CurrentThread.h"
#include "Logger.h"
TcpServer::TcpServer(EventLoop * loop,int num,short port_):
    masterloop(loop),
    numthreads(num),
    started(false),
    port(port_),
    eventloopthreadpool(new EventLoopThreadPool(masterloop,num)),
    acceptor(new Event(masterloop)),
    listenfd(Socket_Bind_Listen(port))
{
    
    acceptor->Setfd(listenfd);
    std::cout << "after set fd"<<listenfd << std::endl;
    SignalHandler_PIPE();
    std::cout << "begin set non blocking "<<listenfd << std::endl;
    SetSocketOpt_NonBlock(listenfd);
}

void TcpServer::Start(){
    eventloopthreadpool->Start();
    std::cout <<"TcpServer will Start()"<<std::endl;
    std::cout << "TcpServer Start "<<listenfd << std::endl;
    acceptor->SetEventType(EPOLLIN | EPOLLET);
    acceptor->SetReadHandler(std::bind(&TcpServer::HandleNewConn, this));
    acceptor->SetConnectionHandler(std::bind(&TcpServer::HandleCurrentConn, this));
    masterloop->AddToEpoll(acceptor, 0);// 0???
    started = true;
    std::cout << __FILE__ << __LINE__ <<std::endl;
}

void TcpServer::HandleNewConn() {
    std::cout << CurrentThread::tid()<<std::endl;
    std::cout << "TcpSERVER handle new conn"<<std::endl;
  struct sockaddr_in client_addr;
  std::cout << __FILE__ << __LINE__ << std::endl;
  memset(&client_addr, 0, sizeof(struct sockaddr_in));
  socklen_t client_addr_len = sizeof(client_addr);//must init!
  int accept_fd = 0;
  std::cout << __FILE__ << __LINE__ << std::endl;
  while ((accept_fd = accept(listenfd, (struct sockaddr *)&client_addr,
                             &client_addr_len)) > 0) {
  std::cout << __FILE__ << __LINE__ << std::endl;
    EventLoop *loop = eventloopthreadpool->GetNextLoop();
  std::cout << __FILE__ << __LINE__<<":  "<<accept_fd << std::endl;
  std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << ":"
        << ntohs(client_addr.sin_port)<<std::endl;
    /*
    // TCP的保活机制默认是关闭的
    int optval = 0;
    socklen_t len_optval = 4;
    getsockopt(accept_fd, SOL_SOCKET,  SO_KEEPALIVE, &optval, &len_optval);
    cout << "optval ==" << optval << endl;
    */
    // 限制服务器的最大并发连接数
  std::cout << __FILE__ << __LINE__ << std::endl;
    if (accept_fd >= MAX_CONN) {
      close(accept_fd);
      continue;
    }
    // 设为非阻塞模式
    SetSocketOpt_NonBlock(accept_fd); 

    SetSocketOpt_NonDelay(accept_fd);
    std::shared_ptr<RequestContent> req_info(new RequestContent(loop, accept_fd));
    req_info->GetEvent()->SetHolder(req_info);
    masterloop->QueueInLoop(std::bind(&RequestContent::Init_Event, req_info));
  }
  acceptor->SetEventType(EPOLLIN | EPOLLET);
}
