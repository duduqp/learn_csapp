#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>


extern int errno;
static void print_conf(const char *msg,int name){
    long lim;

    errno=0 ;
    lim = sysconf(name);
    if(lim==-1)
    {
        if(errno == 0)
        {
            fprintf(stdout,"%s indeterminate conf",msg);
            exit(0);
        }else{
            perror("sysconf()");
            exit(0);
        }

    }else{
            fprintf(stdout,"%s limit in current platform:%ld",msg,lim);
            return ;
    }


}

int main(int argc,char ** argv)
{
    print_conf("SC_PAGESIZE",_SC_PAGESIZE);

    return 0;
}

