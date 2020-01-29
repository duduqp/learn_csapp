#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unp.h>
#define BUFSIZE 4096
#define SERV_PORT 6666


static int log4cli()
{
    //return letters write in log file
    char * log[BUFSIZE];
    int numread =0;
    while((numread=read(STDIN_FILENO,log,BUFSIZE))<=0)
    {
        if(numread==0)//eof
        {
            break;
        }else{
            if(errno==EINTR)
            {
                continue;
            }else{
                perror("read error");
                exit(-1);
            }
        }
    }

    int logfd = open("serverlog",O_WRONLY|O_TRUNC|O_CREAT,0755);
    if(logfd<0)
    {
        perror("open error");
        exit(-1);
    }

    //wirte in log file
    if(numread!=write(logfd,log,numread))
    {
        perror("write error");
        exit(-1);
    }
    fprintf(stdout,"log success -> serverlog");
    Close(logfd);
    return numread;

}


int main(int argc,char ** argv)
{
    int lisfd,confd;
    pid_t con_child;
   socklen_t  clilen;
   struct sockaddr_in servaddr,cliaddr;
    
    lisfd=Socket(AF_INET,SOCK_STREAM,0);
    //init addr struct
    
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);


    Bind(lisfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    Listen(lisfd,10);

    while(true)
    {
        clilen=sizeof(cliaddr);
        confd=Accept(lisfd,(struct sockaddr *)&cliaddr,&clilen);
        if((con_child=fork())==0)//child
        {
            Close(lisfd);
            log4cli();
            exit(0);
        }
        //both child and parent need to close 
            Close(confd);
        
    }

    return 0;
}

