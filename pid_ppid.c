#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
    pid_t p = getpid();
    pid_t pp = getppid();
    printf("my pid : %d\n",p);
    printf("my parent id : %d\n",pp);
    return 0;
}

