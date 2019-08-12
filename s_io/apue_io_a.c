#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#define SIZE 1024

int main()
{   
    char buff[SIZE];
    /* fwide  freopen fopen fflush
    
    
    */

    // usage for fprintf  
    // fprintf(stdout,"stdin buff mode wide or single?: %d",fwide(stdin,0));

    // usage for setbuff change buffmode
    //

    // usage for fopen open a stream 打开流
    FILE * f = fopen("README.md","r");
    if(f==NULL)
    {
        perror("fopen()");
        exit(1);
    }

    fgets(buff,20,f);
    fprintf(stdout,"%s",buff);
    
    return 0;
}

