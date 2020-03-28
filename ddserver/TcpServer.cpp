#include "TcpServer.h"
#include "util.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>

TcpServer::TcpServer(EventLoop * loop,int num,short port_):
    masterloop(loop),
    numthreads(num),
    started(false),
    port(port_),
    eventloopthreadpool(new EventLoopThreadPool(masterloop,num)),
    acceptor(new Event(loop)),
    listenfd(Socket_Bind_Listen(port))
{
    SetSocketOpt_NonBlock(listenfd);
    acceptor->Setfd(listenfd);
    SignalHandler_PIPE();
}

void TcpServer::Start(){
    eventloopthreadpool->Start();
  acceptor->SetEventType(EPOLLIN | EPOLLET);
  acceptor->SetReadHandler(std::bind(&TcpServer::HandleNewConn, this));
  acceptor->SetConnectionHandler(std::bind(&TcpServer::HandleCurrentConn, this));
  masterloop->AddToEpoll(acceptor, 0);
  started = true;
}
void TcpServer::HandleNewConn() {
  struct sockaddr_in client_addr;
  memset(&client_addr, 0, sizeof(struct sockaddr_in));
  socklen_t client_addr_len = sizeof(client_addr);//must init!
  int accept_fd = 0;
  while ((accept_fd = accept(listenfd, (struct sockaddr *)&client_addr,
                             &client_addr_len)) > 0) {
    EventLoop *loop = eventloopthreadpool->GetNextLoop();
    LOG << "New connection from " << inet_ntoa(client_addr.sin_addr) << ":"
        << ntohs(client_addr.sin_port);
    /*
    // TCP的保活机制默认是关闭的
    int optval = 0;
    socklen_t len_optval = 4;
    getsockopt(accept_fd, SOL_SOCKET,  SO_KEEPALIVE, &optval, &len_optval);
    cout << "optval ==" << optval << endl;
    */
    // 限制服务器的最大并发连接数
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
