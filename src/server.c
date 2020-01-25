#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#define SERV_PORT 6666
#define SERV_IP "127.0.0.1"

int main()
{
    struct sockaddr_in serv_addr,cli_addr;
    int listenfd;

    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<0)
    {
        perror("socket create error");
        exit(-1);
    }

    inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr);
    serv_addr.sin_family=AF_INET;
//   serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);
    bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    listen(listenfd,128);//max 128
    socklen_t clisize=sizeof(cli_addr);
    int cli_fd =  accept(listenfd,(struct sockaddr *)&cli_addr,&clisize);// input, input-output parameter
    int numrd;

    char buf[BUFSIZ];
    numrd=read(cli_fd,buf,BUFSIZ);
    if(numrd <0)
    {
        perror("read remote error");
        exit(-1);
    }

    int logfd = open("client msg log",O_CREAT|O_EXCL|O_WRONLY,0755);
    if(logfd<0)
    {
        perror("open log file");
        exit(-1);
    }

    if(numrd!=write(logfd,buf,numrd))
    {
        perror("write log error");
        exit(-1);
    }


    write(cli_fd,buf,numrd);
    close(listenfd);
    close(logfd);
    close(cli_fd);
    return 0;
}

