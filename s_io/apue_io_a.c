#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define SIZE 1024
static void file_error_handler(FILE * f,const char * msg)
{
    perror(msg);
    fclose(f);
    exit(1);
}


int main()
{   
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
    /*
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
    fclose(f);
    */

    //note that 10 contains a '/0'
    /* if the line more than >9 characters(exclude the '/0') fgets will only read 9 and next exec will start at 10th charc
    */
    FILE  * f = fopen("IO_TEST","rw");
    
    if(!f)
    {
        perror("fopen()");
    }

    char buff[20] ;
    char txt[20] = "1234567890";
    if(!fputs(txt,f))
    {
        file_error_handler(f,"fgets()");
    }
    
    
    if(!fgets(buff,5,f))
    {
        file_error_handler(f,"fgets()");
    }
   
    fprintf(stdout,"after first  call fgets(5) : %s",buff);

    if(!fgets(buff,5,f))
    {
        file_error_handler(f,"fgets()");
    }
   
    fprintf(stdout,"after second  call fgets(5) : %s",buff);

    FILE * o = fopen("OUT_TEST","w");
    if(!fputs(buff,o))
    {
        file_error_handler(o,"fputs()");
    }

    fclose(f);
    fclose(o);
    
    
    exit(0);
}

