#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc,char ** argv)
{
    if(argc<3)
    {
        fprintf(stderr,"usage: old newlnk ");
        exit(1);
    }
    if(link(argv[1],argv[2])<0)
    {
        perror("link error");
        exit(0);
    }
    return 0;
}

