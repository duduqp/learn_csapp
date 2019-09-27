#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_LINE 100
int main(int argc,char ** argv)
{
    int fd;
    ssize_t old_val;
    char info[MAX_LINE];

    fprintf(stdout,"BEGIN");
    fd=open("/proc/sys/kernel/pid_max",(argc > 1)? O_RDWR:O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        exit(1);
    }

    old_val = read(fd,info,MAX_LINE);
    if(old_val == -1)
    {
        perror("read");
        exit(1);
    }

    if(argc>1)
    {
        if(write(fd,argv[1],strlen(argv[1]))!=strlen(argv[1]))
        {
            fprintf(stdout,"write error");
            exit(1);
        }

        fflush(NULL);
        pid_t p;
        p=fork();
        if(p<0)
        {
            perror("fork");
            exit(1);
        }

        if(p == 0)
        {
            //child process
            execl("/bin/cat","/bin/cat","/proc/sys/kernel/pid_max",NULL);
            perror("execl");
            exit(1);
        }
        
        wait(NULL);
        exit(0);
    }
    exit(0);
}

