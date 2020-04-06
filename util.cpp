#include "util.h"
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <utility>
#include <cstring>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include "Logger.h"
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <iostream>
//blocking use only
ssize_t readn(int fd,void * buffer,size_t n)
{
    char * buf=static_cast<char *>(buffer);
    int remain=n;
    int readcount=0;
    ssize_t readnum=0;
    while(remain>0)
    {
        if((readcount=read(fd,buffer,remain))<=0)
        {
            if(readcount==0)
            {
                break;
            }
            if(errno==EINTR)
            {
                readcount=0;
            }else if(errno==EAGAIN)
            {
                return readnum; 
            }else{
                perror("read error");
                return -1;//truely error,log to do
            }
        }
        
        readnum+=readcount;
        remain-=readcount;
        buf+=readcount;
    }

    return readnum;//return number byte already read in
}

ssize_t readn(int fd,std::string & inbuffer)
{
    //inbuffer c_str is const ,cannot be write in
    //so need to impl a new version readn
    int readcount=0;
    ssize_t readnum=0;
    while(true){
        char buffer[MAX_BUF];
        if((readcount=read(fd,buffer,MAX_BUF))<=0)
        {
            if(readcount==0)
            {
                break;
            }

            if(readcount<0)
            {
                if(errno==EINTR)
                {
                    continue;
                }else if(errno==EAGAIN)
                {
                    return readnum;
                }else{
                    perror("read error");//log to do
                    return -1;
                }
            }
            //write to string
            readnum+=readcount;
           buffer[readcount]='\0';
            inbuffer.append(std::string(buffer));
        }

    }
    return readnum;
}

ssize_t writen(int fd,void * buffer,size_t n)
{
    char * buf=static_cast<char *>(buffer);
    int remain=n;
    int writecount=0;
    ssize_t writenum=0;
    while(remain>0)
    {
        if((writecount=write(fd,buffer,remain))<=0)
        {
            if(writecount==0)
            {
                continue;//if nonblocking ,try again ;if blocking write fail ,try again;
            }
            if(errno==EINTR)
            {
                writecount=0;
            }else if(errno==EAGAIN)
            {
                return writenum; 
            }else{
                perror("write error");
                return -1;//truely error,log to do
            }
        }
        
        writenum+=writecount;
        remain-=writecount;
        buf+=writecount;
    }

    return writenum;//return number byte already read in
}

ssize_t writen(int fd,std::string & outbuffer)
{
    int remain=outbuffer.size();
    int writenum=0;
    int writecount=0;
    const char * str=outbuffer.c_str();
    while(remain>0)
    {
        if((writecount=write(fd,str,remain))<0)
         {
                if(errno==EINTR)
                {
                    //intr by signo
                    continue;
                }else if(errno==EAGAIN)
                {
                    break;
                }else{
                    perror("write error");
                    return -1;
                }
            
         }
        writenum+=writecount;
        str+=writecount;
        remain-=writecount;
    }

        
    if(writenum==outbuffer.size())
    {
        outbuffer.clear();//clear safe
    }else{
        outbuffer=outbuffer.substr(writenum);
    }
    return writenum;
}


void Default_Error_Handler()
{
    LOG << "Default Error Handler";
    exit(-1);
}

void SignalHandler_PIPE()
{
   struct sigaction sa;
   memset(&sa,0,sizeof(sa));
   sa.sa_handler=SIG_IGN;
   sa.sa_flags=0;
   if(sigaction(SIGPIPE,&sa,NULL))
   {
        LOG<<"sigaction error";
   }
}

void SetSocketOpt_NonLinger(int fd){
    struct linger linger_;
    linger_.l_onoff=1;
    linger_.l_linger=30;
    setsockopt(fd,SOL_SOCKET,SO_LINGER,(const char *)&linger_,sizeof(linger_));
}

void SetSocketOpt_NonDelay(int fd)
{
    int flag=1;
    setsockopt(fd,IPPROTO_TCP,TCP_NODELAY,(void *)&flag,sizeof(flag));
}

void SetSocketOpt_NonBlock(int fd)
{
    int flag=fcntl(fd,F_GETFL,0);
    flag|=O_NONBLOCK;

    if((fcntl(fd,F_SETFL,flag))==-1)
    {
        LOG<<"SetSocketOpt_NonBLOCK";
    }
    std::cout << "return from set non block"<<fd<<std::endl;
}

void ShutDownWR(int fd)
{
    shutdown(fd,SHUT_RDWR);
}
void ShutDownW(int fd)
{
    shutdown(fd,SHUT_WR);
}
void ShutDownR(int fd)
{
    shutdown(fd,SHUT_RD);
}
ssize_t readn(int fd, std::string &inBuffer, bool &zero) {
  ssize_t nread = 0;
  ssize_t readSum = 0;
  while (true) {
    char buff[MAX_BUF];
    if ((nread = read(fd, buff, MAX_BUF)) < 0) {
      if (errno == EINTR)
        continue;
      else if (errno == EAGAIN) {
        return readSum;
      } else {
        perror("read error");
        return -1;
      }
    } else if (nread == 0) {
      // printf("redsum = %d\n", readSum);
      zero = true;
      break;
    }
    // printf("before inBuffer.size() = %d\n", inBuffer.size());
    // printf("nread = %d\n", nread);
    readSum += nread;
    // buff += nread;
    inBuffer += std::string(buff, buff + nread);
    // printf("after inBuffer.size() = %d\n", inBuffer.size());
  }
  return readSum;
}
int Socket_Bind_Listen(short port)
{
  // 检查port值，取正确区间范围
    std::cout << __LINE__<<"in sock init"<<port << std::endl;
  if (port < 0 || port > 65535) return -1;

    std::cout << __LINE__<<"in sock init"<<port << std::endl;
  // 创建socket(IPv4 + TCP)，返回监听描述符
  int listen_fd = 0;
  if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) return -1;

    std::cout << __LINE__<<"in sock init"<<port << std::endl;
  // 消除bind时"Address already in use"错误
  int optval = 1;
  if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &optval,
                 sizeof(optval)) == -1) {
    close(listen_fd);
    return -1;
  }

    std::cout <<__LINE__<< "in sock init"<<port << std::endl;
  // 设置服务器IP和Port，和监听描述副绑定
  struct sockaddr_in server_addr;
  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons((unsigned short)port);
  if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      -1) {
    close(listen_fd);
    return -1;
  }

    std::cout <<__LINE__<< "in sock init"<<port << std::endl;
  // 开始监听，最大等待队列长为LISTENQ
  if (listen(listen_fd, 2048) == -1) {
    close(listen_fd);
    return -1;
  }

    std::cout <<__LINE__<< "in sock init"<<port << std::endl;
  // 无效监听描述符
  if (listen_fd == -1) {
    close(listen_fd);
    return -1;
  }
  std::cout << "sock listenfd:"<<listen_fd << std::endl;
  return listen_fd;
}

ssize_t peekn(int sockfd,void * buf,size_t len)
{
    while(1)
    {
        int ret=recv(sockfd,buf,len,MSG_PEEK);
        if(ret==-1&&errno ==EINTR)
        {
            continue;
        }
        return ret;
    }
}

ssize_t readblock(int fd,void * buf,int blksize,char sep)
{
    //impl by peekn,socket fd only
    int ret,nread;
    char * bufp=static_cast<char *>(buf); 
    while(blksize>0)
    {
        ret=peekn(fd,bufp,blksize);
        if(ret<=0)
        {
            return ret;
        }

        //judge freshly read data has sep or not
        int i=0;
        for(;i<ret;++i)
        {
            if(bufp[i]==sep)
            {
                ret=readn(fd,bufp,i+1);
                if(ret!=i+1)
                {
                    perror("readn error");
                    exit(-1);
                }
                return ret;
            }
        }
        if(ret>blksize)
        {
            perror("peekn error");
            exit(-1);
        }
        blksize-=ret;
        ret=readn(fd,bufp,blksize);
        if(ret!=blksize)
        {
            perror("readn error");
            exit(-1);
        }
        bufp+=ret;
    }
    return -1;
}


