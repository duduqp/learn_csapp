#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <fcntl.h>
#include "../header/wrap.h"
#define BUFSIZE 4096

int main(int argc,char ** argv)
{
    /*
    if(argc < 3)
    {
        perror("argument invalid");
        exit(-1);
    }



    int fdin,fdout;
    fdin=open(argv[1],O_RDONLY);
    if(fdin < 0)
    {
        perror("file open error");
        exit(-1);
    }

    fdout=open(argv[2],O_WRONLY|O_CREAT|O_EXCL,0644);
    if(fdout<0)
    {
        perror("file open error");
        exit(-1);
    }

    int num;
    char buf[BUFSIZE];
    while((num=read(fdin,buf,BUFSIZE))>=0)
    {
        if(num == 0)
        {
            fprintf(stdout,"file %s have read finished",argv[1]);
            break;
        }
        if(write(fdout,buf,num)!=num)
        {
            perror("write error");
            exit(-1);
        }
    }

    if(close(fdin)<0||close(fdout))
    {
        perror("file close error");
        exit(-1);
    }



    printf("file %s copy to %s success!\n",argv[1],argv[2]);
    */

    /*make a hole file and copy the same*/
     
     int fdin,fdout;
     fdin=Open_r(argv[1],O_RDONLY);
     fdout=Open_w(argv[2],O_WRONLY|O_CREAT|O_EXCL,0755);

     off_t offset=lseek(fdin,0,SEEK_CUR);
     fprintf(stdout,"file %s len %ll",argv[1],(long long)offset);

    char buf[BUFSIZE];
    int numrd;
    while((numrd=)
     
     
     
     
     
     
     
     
     
     
     
     
     
    
    return 0;
}

