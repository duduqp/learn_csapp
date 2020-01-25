#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";



int main(void)
{
    int fd;

    if((fd=open("file.hole",O_RDWR|O_EXCL|O_CREAT))<0)
    {
        perror("creat error");
        exit(1);
    }

    if(write(fd,buf1,strlen(buf1))!=10)
    {
        perror("write error");
        exit(1);
    }

    if(lseek(fd,16384,SEEK_SET)==-1)
    {
        perror("lseek error");
        exit(1);
    }

    if(write(fd,buf2,strlen(buf2))!=10)
    {
        perror("write error");
        exit(1);
    }



    exit(0);
}

