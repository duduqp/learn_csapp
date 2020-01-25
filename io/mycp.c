#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 4096
int main(int argc,char ** argv)
{
    if(argc<3)
    {
        fprintf(stderr,"usage:%s input output",argv[0]);
        exit(1);
    }
    char buf[BUFSIZE];
    int fd1;
    int n;
    if((fd1=open(argv[1],O_RDONLY))<0)
    {
        perror("open in");
        exit(1);
    }

    int fd2;
    if((fd2=open(argv[2],O_WRONLY|O_CREAT|O_EXCL))<0)
    {
        perror("open out");
        exit(1);
    }

    if(read(fd1,buf,5)<0)
    {
        perror("read");
        exit(1);
    }

    if(write(fd2,buf,5)!=5)
    {
        perror("write");
        exit(1);
    }
    exit(0);
}

