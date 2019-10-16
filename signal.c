#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "mysignal.h"

//fprintf is not async_signal_safe
void printsigset(FILE * of ,const char * prefix,const sigset_t *sigset)
{
    int sig,cnt;

    cnt = 0;
    for(sig = 1;sig< NSIG;++sig)
    {
        if(sigismember(sigset,sig)){
            cnt++;
            fprintf(of,"%s%d (%s)\n",prefix,sig,strsignal(sig));
        }
    }

    if(cnt == 0)
    {
        fprintf(of,"%s <empty signal set>\n",prefix);
    }

}

int printsigmask(FILE * of,const char * msg)
{
    sigset_t currmask;

    if(msg!=NULL)
    {
        fprintf(of,"%s",msg);
    }

    if(sigprocmask(SIG_BLOCK,NULL,&currmask)==-1)
    {
        return -1;
    }

    printsigset(of,"\t\t",&currmask);
    return 0;
}

int printpendingsigs(FILE *of,const char *msg)
{
    sigset_t pendingsigs;

    if(msg!=NULL)
    {
        fprintf(of,"%s",msg);

        if(sigpending(&pendingsigs)==-1)
        {
            return -1;
        }
    }

    printsigset(of,"\t\t",&pendingsigs);

    return 0;
}

int main()
{
    printf("Hello world\n");
    return 0;
}

