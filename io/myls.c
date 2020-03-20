#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

static void mode_str(int mode,char * ret)
{
    strcpy(ret,"----------");
    if(S_ISDIR(mode)) ret[0]='d';
}
int main(int argc,char ** argv)
{
    if(argc<1)
    {
        fprintf(stdout,"default myls .");
    }
    

    printf("Hello world\n");
    return 0;
}

