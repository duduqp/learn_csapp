#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char ** argv)
{
    if(argc!=3)
    {
        fprintf(stderr,"param err");
        exit(0);
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    //retrun 1 if res will overflow 0 otherwise 

    int flag = ((a>0)&&(b>0)&&((a+b)<0))||((a<0)&&(b<0)&&((a+b)>0));
    if(flag==0) 
    {
        fprintf(stdout,"safe for add");
    }
    else{
        fprintf(stderr,"that will overflow");
    }

}

