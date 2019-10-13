#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int status;
    pid_t pid;

    if(!fork())//CHILD
    {
        printf("this is child process,will exit(0)\n");
        exit(EXIT_SUCCESS);
    }

    pid = wait(&status);
    if(pid == - 1)
    {
        perror("wait");
        exit(EXIT_FAILURE);
    }

    printf("pid=%d\n",pid);//success
    
    //check child terminate status
    if(WIFEXITED(status))
    {
        printf("normal EXIT_SUCCESS with status:%d\n",WEXITSTATUS(status));
        exit(EXIT_SUCCESS);
    }else if(WIFSIGNALED(status)){
        printf("signaled EXIT with signalnumber:%d coredump info:%s",
               WTERMSIG(status),WCOREDUMP(status)?"yes ,coredump":"no ,other reason");
        exit(EXIT_FAILURE);
    }else{
        printf("stoped for some reasons\n");
        exit(EXIT_FAILURE);
    }

    printf("Hello world\n");
    return 0;
}

