#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main()
{
    pid_t c = fork();
    if(c == 0)
    {
        //parent process
        printf("this is parent process:%d",getpid());
    }else{
        
        printf("this is child process:%d,it will exec conf",getpid());
    execlp("./conf",NULL);
    }
    return 0;
}

