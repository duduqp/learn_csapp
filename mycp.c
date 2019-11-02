#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#define BUFSIZE 1024

int main(int argc,char **argv)
{
    int rd;
    int rd_fd,wt_fd;
    char buf[BUFSIZE];

    if(argc<3)
    {
        fprintf(stderr,"invalid argument");
        exit(1);
    }

    if((rd_fd=open(argv[1],O_RDONLY)) == -1)
    {
        perror("read file open error");
        exit(1);
    }

    if((wt_fd=open(argv[2],O_WRONLY|O_CREAT,0644))== -1)
    {
        perror("write file open error");
        exit(1);
    }

    while((rd = read(rd_fd,buf,BUFSIZE)) > 0)
    {
        fprintf(stdout,"%d",rd);
        if(write(wt_fd,buf,rd)!=rd)
        {
            perror("write error");
            exit(1);
        }
    }
    if(rd == -1)
    {
        perror("read error");
        exit(1);
    }

    //close fd
    if(close(rd_fd) == -1||close(wt_fd) == -1)
    {
        perror("close error");
        exit(1);
    }


    return 0;
}

