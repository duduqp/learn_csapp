#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int main()
{
    off_t sz;
    int fd;
    if((fd=open("file_hole",O_RDONLY))<0)
    {
        perror("open error");
        exit(1);
    }

    if((sz=lseek(fd,0L,2))<0)
    {
        perror("lseek error");
        exit(1);
    }


    printf("file:%s  size:%ld","file_hole",sz);
    exit(0);
}

