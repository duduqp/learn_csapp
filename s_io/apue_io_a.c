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
    /*
    FILE * f = fopen("README.md","r");
    if(f==NULL)
    {
        perror("fopen()");
        exit(1);
    }

    fgets(buff,20,f);
    fprintf(stdout,"%s",buff);
    int r = fclose(f); 
    if(r==EOF)
    {
        perror("fclose()");
    }
    */

    //getc fgetc getchar [put]
    //also ferror feol check specific error
    
    FILE * f = fopen("IO_TEST","w");
    int i = 0;
    int ret_val=0;
    for(;i<13&&(ret_val=fputc('*',f))!=EOF;++i)
    {
        ;
    }
    if(ret_val==EOF)
    {
        perror("fputc()");
    }else{
        fprintf(stdout,"succ");
    }
    //not a marco
    exit(0);
}

