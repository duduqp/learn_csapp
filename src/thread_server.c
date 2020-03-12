#include <stdio.h>
#include "BlockQueue.h"
#include <unp.h>
#define BUF_SIZE 4096

void loop_func(int fd)
{
    //todo with fd in loop
    char buf[BUF_SIZE];
    int count;
    while((count=recv(fd,buf,sizeof(buf),0))>=0)
    {
        if(count==0)
        {
            if(EINTR==errno) continue;
            break;
        }
        if(count!=send(fd,buf,count,0))
        {
            perror("send error");
            //log
            continue;
        }
    }
    if(count<0)
    {
        perror("recv error");
    }
    pthread_exit(NULL);
}

void thread_run(void * arg)
{
    pthread_t tid=pthread_self();
    pthread_detach(tid);

    block_queue * bq=(block_queue *)arg;
    while(1){
        int fd=block_queue_pop(bq);
        printf("thread: %d : get fd in thread queue %d\n",tid,fd);
        loop_func(fd);
    }
}

int tcp_server_listen(short port)
{
    int sockfd;
    sockfd=Socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    
    Bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    Listen(sockfd,128);
    return sockfd;
}





int main()
{
    block_queue * bq;
    block_queue_init(bq,128);





    return 0;
}

