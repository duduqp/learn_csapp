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
    if(fcntl(fd,F_SETFL,flag)<0)
    {
        LOG<<"SetSocketOpt_NonLinger";
    }

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
