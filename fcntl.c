#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
int main(int argc,char ** argv)
{
    int flags,acmode;
    int fd;

    if(argc<2)
    {
        fprintf(stderr,"usage fcntl [filename]\n");
        exit(0);
    }


    fd = open(argv[1],O_RDWR | O_CREAT | O_EXCL,0777);
    if(fd == -1)
    {
        perror("open");
        exit(0);
    }

    flags=fcntl(fd,F_GETFL);
    if(flags == -1)
    {
        perror("fcntl");
        exit(0);
    }
    acmode = flags & O_ACCMODE;
    if(acmode == O_WRONLY)
    {
        printf("file_a.txt is opened as writeonly\n");
        exit(0);
    }else if(acmode == O_RDWR){
        printf("file_a.txt is opened as readwrite\n");
        exit(0);
    }else{
        printf("file_a.txt is opened as readonly\n");
        exit(0);
    }
    exit(0);
}

