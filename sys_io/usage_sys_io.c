#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#define MAXN 1024

int main()
{
    char buf[MAXN];
    int fd;
    fd = open("symbol_copy",O_RDONLY);//can deref a symbol-link as well,if not o_creat,can ignore perm
    if(fd == -1)
    {
        perror("open()");
        exit(0);
    }

    //note open use a min and non_used num for fd
    //if closed stdin(0 default)
    //then open any fd will be 0 replacely
    /*
    if(close(STDIN_FILENO)==-1)
    {
        perror("close()");
        exit(0);
    }

    fd = open("sys_io.c",O_RDONLY);//now fd must be 0
    fprintf(stdout,"%d",fd);
    */




    //read return -1:err 0:EOF
    //note read never append a '\0'!
    /*
     ssize_t rd_num = read(fd,buf,MAXN);
    if(rd_num == -1)
    {
        perror("read()");
        exit(0);
    }

    //must append a '\0' if a str read-in
    buf[rd_num] = '\0';
    printf("read-in data %s\n",buf);
    */




    //lseek
    //to calc file length
    off_t size = lseek(fd,0,SEEK_END);
    off_t start = 0;
    printf("file size: %ld BYTES",(size-start));



    exit(0);
}

