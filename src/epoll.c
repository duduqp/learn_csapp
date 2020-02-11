#include <stdio.h>
#include "../header/wrap.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <strings.h>
#include <stdlib.h>
#define MAXLINE 8192
#define SERV_PORT 8000
#define OPEN_MAX 500


int main(int argc,char **argv)
{
    int i,listenfd,connfd,sockfd;
    int n,num=0;
    ssize_t nready,efd,res;
    char buf[MAXLINE],str[INET_ADDRSTRLEN];
    socklen_t clilen;

    struct sockaddr_in cli_addr,serv_addr;
    struct epoll_event evts[OPEN_MAX];
    struct epoll_event tep;


    listenfd=Socket(AF_INET,SOCK_STREAM,0);
    
    bzero(&serv_addr,sizeof(struct sockaddr_in));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    Bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    Listen(listenfd,128);

    efd=epoll_create(OPEN_MAX);
    if(efd==-1)
    {
        perror("epoll create");
        exit(-1);
    }

    tep.events = EPOLLIN;//template struct 
    res=epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&tep);
    if(res==-1)
    {
        perror("epoll ctl");
        exit(-1);
    }

    for(;;)
    {
        nready=epoll_wait(efd,evts,sizeof(evts)/sizeof(evts[0]),-1);
        if(nready==-1)
        {
            perror("epoll wait");
            exit(-1);
        }

        for(int i=0;i<nready;++i)
        {
            //check evts returned
            if(evts[i].events==EPOLLIN)
            {
                if(evts[i].data.fd==listenfd)//a new connect client also mean a EPOLLIN
                {
                    clilen=sizeof(cli_addr);//a new conn
                    connfd=Accept(listenfd,(struct sockaddr *)&cli_addr,&clilen);//clilen both in and out

                    printf("received %s from %d",inet_ntop(AF_INET,&cli_addr.sin_addr,str,sizeof(str)),
                           ntohs(cli_addr.sin_port));

                    tep.events=EPOLLIN;tep.data.fd=connfd;
                    res=epoll_ctl(efd,EPOLL_CTL_ADD,connfd,&tep);
                    if(res==-1)
                    {
                        perror("epoll ctl");
                        exit(-1);
                    }

                }else{
                    //truely readable client
                    sockfd=evts[i].data.fd;
                    n=readn(sockfd,buf,MAXLINE);

                    if(n==0)
                    {
                        //end client close connection
                       //delete from listen set(rb-tree)
                       if(epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL)<0)
                       {
                            perror("epoll ctl");
                            exit(-1);
                       }
                       close(sockfd);//also close cli fd;

                    }else{
                        //process read data
                        writen(sockfd,buf,n);
                        fprintf(stdout,"client write:%s",buf);
                        
                    }
                }//not listenfd
            }else{
                continue;
            }
        }
    }




    exit(0);
}
