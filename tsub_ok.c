#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char ** argv)
{
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    //test if a-b is overflow
    int flag=((a>0)&&(b<0)&&(a-b<0))||((a<0)&&(b>0)&&(a-b>0));
    if(flag==0)
    {
        fprintf(stdout,"it is safe");
    }
    else{
        fprintf(stdout,"will overflow");
    }
    exit(0);
}

