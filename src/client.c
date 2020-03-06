#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <sys/types.h>
#include "../header/unp.h"

#define BUF_SIZE 4096

int main()
{
    struct sockaddr_in serv_addr;
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(8888);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    int conn_fd=Socket(AF_INET,SOCK_STREAM,0);

    //connect three way shakehand
    Connect(conn_fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    
    //read from stdin
    char buf[BUF_SIZE];
    int stdincount=0;
    while(fgets(buf,BUF_SIZE,stdin)!=NULL)
    {
        
        stdincount=sizeof(buf);
        buf[stdincount]='\0';
        printf("%s\n",buf);
        if(write(conn_fd,buf,stdincount+1)<stdincount+1)
        {
            fprintf(stdout,"write error\n");
            close(conn_fd);
            exit(-1);
        }
    }
    printf("connection over");
    close(conn_fd);
    return 0;
}

