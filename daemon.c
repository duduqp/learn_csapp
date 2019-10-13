#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fs.h>

int main(void)
{
    pid_t pid;
    int i;

    //create new process
    pid = fork();
    if(pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(pid!=0)
    {
        //parent
        exit(EXIT_SUCCESS);
    }

    //create new session and process group
    if(setsid()==-1)
    {
        perror("setsid");
        exit(EXIT_FAILURE);
    }

    //set working dir to root
    if(chdir("/")==-1)
    {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    //clear all fd 
    for(i=0;i<NR_OPEN;i++)
    {
        close(i);
    }

    //redirect fd 012 to /dev/null
    open("/dev/null",O_RDWR);
    dup(0);
    dup(0);
    printf("daemon code\n");
    exit(EXIT_SUCCESS);
}

