#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <unp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define MAX_LINE  4096

//process signal
static void sig_hdl(int signo)
{
    

}



int main(int argc,char ** argv)
{
    int connect_fd;
    connect_fd=Socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in serv_addr;
    socklen_t serv_len;
    bzero(&serv_addr,sizeof(sockaddr_in));
    
    //inetpton
    inet_pton(AF_INET,argv[1],&serv_addr.sin_addr);//not sin_addr.s_addr!!!
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);

    serv_len=sizeof(serv_addr);
    int res=connect(connect_fd,(struct sockaddr *)&serv_addr,serv_len);//never sizeof(...)
    if(res<0)
    {
        perror("connect");
        exit(-1);
    }

    int n = 0 ;//readcount

    //select
    fd_set readmask,allmask;
    FD_ZERO(&allmask);
    FD_SET(0,&allmask);//stdin!!!
    FD_SET(connect_fd,&allmask);//connect listenfd


    int ready=0;
    char addr[MAX_LINE],text[MAX_LINE];
    for(;;)
    {
        readmask=allmask;//update current readset
        if((ready=select(connect_fd+1,&readmask,NULL,NULL,NULL))<0)//no write no exception blocking
        {
            perror("select");
            close(connect_fd);
            exit(-1);
        } 

        if()
        //polling
        for(int i = 0;i<ready;++i)
        {
            if(FD_ISSET())
            {

            }else{

            }
        }
    
    
    
    }
    exit(0);
}

