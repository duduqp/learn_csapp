#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define CMD_SIZE 200
#define BUF_SIZE 1024


int main(int argc,char ** argv)
{
    int fd,j,numblocks;
    char shellcmd[CMD_SIZE];
    char buf[BUF_SIZE];

    if(argc<2||strcmp(argv[1],"--help")==0)
    {
        fprintf(stderr,"%s temp-file [num-1kb-blocks] \n",argv[0]);
        exit(EXIT_FAILURE);
    }

    numblocks = atoi(argv[2]);

    fd = open(argv[1],O_WRONLY | O_CREAT | O_EXCL,0600);
    if(fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if(unlink(argv[1])==-1)
    {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    for(j = 0;j<numblocks;j++)
    {
        if(write(fd,buf,BUF_SIZE)!=BUF_SIZE)
        {
            fprintf(stderr,"failed write (partial)\n");
            exit(EXIT_FAILURE);
        }
    }

    snprintf(shellcmd,CMD_SIZE,"df -k ");
    system(shellcmd);

    if(close(fd)==-1)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }
    system(shellcmd);
    exit(EXIT_SUCCESS);
}

