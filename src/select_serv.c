#include <stdio.h>
#include "../header/wrap.h"
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SERV_PORT 8888
#define BUF_SIZE 4096
void _bind(int listenfd,struct sockaddr *serv_addr,socklen_t serv_len)
{
    if(bind(listenfd,serv_addr,serv_len)<0)
    {
        perror("bind error");
        exit(-1);
    }
}

int _socket(int domain,int type,int protocol)
{
    int ret;
    if((ret=socket(domain,type,protocol))<0)
    {
        perror("socket create error");
        exit(-1);
    }
    return ret;
}

void _listen(int listenfd,int backlog)
{
    if(listen(listenfd,backlog)<0)
    {
        perror("listen error");
        exit(-1);
    }
}
void Tcpserverinit(int lfd,struct sockaddr_in * serv_addr,socklen_t serv_len,int backlog)
{
    int opt=1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    _bind(lfd,(struct sockaddr * )serv_addr,serv_len);
    _listen(lfd,backlog);
}

int _accept(int listenfd,struct sockaddr_in * cli_addr,socklen_t * cli_addr_len)
{
    int connect_fd;
    if(connect_fd=accept(listenfd,(struct sockaddr *)cli_addr,cli_addr_len)<0)
    {
        perror("accept error");
        exit(-1);
    }
    return connect_fd;
}




int main()
{
    int lfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv,cli_addr;
    socklen_t serv_l=sizeof(serv);
    bzero(&serv,serv_l);
    serv.sin_family=AF_INET;
    serv.sin_port=htons(8888);
    serv.sin_addr.s_addr=htonl(INADDR_ANY);
    Tcpserverinit(lfd,&serv,serv_l,128);

    fd_set dft_set,lis_set; 
    int upfd=lfd;
    FD_ZERO(&dft_set);
    FD_SET(lfd,&dft_set);


    int new_connect_fd;
    int trigger_count;
    socklen_t cli_addr_len;
    while(1){
        char buf[BUF_SIZE];
        lis_set=dft_set;
        trigger_count=select(upfd+1,&lis_set,NULL,NULL,NULL);//blocking 
        if(trigger_count<0)
        {
            perror("select error");
            exit(-1);
        }


        //consider listen event for  new connection 
        if(FD_ISSET(lfd,&lis_set))
        {
            //a new connection
            //set into lis_set
            cli_addr_len=sizeof(cli_addr);
            new_connect_fd=_accept(lfd,&cli_addr,&cli_addr_len);

            //set into listen fd to be listened next round
            FD_SET(new_connect_fd,&dft_set);

            if(upfd<new_connect_fd)
            {
                upfd=new_connect_fd;
            }

            if(--trigger_count==0)
            {
                continue;//back to while no more extra readable fd 
            }
        }
        //more than listenfd
        //means readable connect(true data)
        for(int i = lfd;i<=upfd;++i)
        {
            if(FD_ISSET(i,&lis_set)){
                //process data input outpur
                int readcount=0;
                while((readcount=read(i,buf,BUF_SIZE))>0)
                {
                    //write to stdout
                    write(STDOUT_FILENO,buf,readcount);
                }
                if(readcount == 0)
                {
                    break;//EOF  
                }else{
                    //readcount<0
                    perror("read error");
                    close(i);
                    //! delete from dft_set
                    FD_CLR(i,&dft_set);
                }
            }
        }
    }//end while

    return 0;
}
