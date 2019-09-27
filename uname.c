#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc,char ** argv)
{
    struct utsname s;

    if(uname(&s)==-1)
    {
        perror("uname");
        exit(1);
    }

    //info has been correctly read into struct s
    printf("user machine:  %s\n",s.machine);
    printf("user system:  %s\n",s.sysname);
    printf("user version:  %s\n",s.version);
    printf("user release:  %s\n",s.release);
    return 0;
}

