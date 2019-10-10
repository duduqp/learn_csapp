#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>


int main(int argc,char ** argv)
{
    struct stat s_buf;
    if(argc<3)
    {
        printf("usage: stat filename initial_text\n");
        exit(1);
    }
    int fd;
    char * postfix = ".txt";
    char  prefix[strlen(argv[1])+1];
    strcpy(prefix,argv[1]);
    char * filename = strcat(prefix,postfix);
    printf("filename : %s",filename);
    fd  =  open(filename,O_WRONLY | O_APPEND | O_CREAT | O_EXCL,0755);
    if(fd == -1)
    {
        perror("open");
        exit(1);
    }

    ssize_t res = write(fd,argv[2],strlen(filename));
    if(res == -1)
    {
        perror("write");
        exit(1);
    }

    if(stat(filename,&s_buf)<0)
    {
        perror("stat");
        exit(1);
    }
    off_t size;
    size = s_buf.st_size;
    printf("file size: %ld",size);
    close(fd);
    exit(0);
}

