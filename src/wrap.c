#include <stdio.h>
#include "../header/wrap.h"
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
FILE * Fopen(const char * path,const char * mode)
{

        FILE * stream=NULL;
    if(strcmp(mode,"r")==0)
    {
        stream=NULL;
        if((stream=fopen(path,"r"))==NULL)
        {
            perror("fopen read error");
            exit(-1);
        }
        return stream;
    }
    if(strcmp(mode,"w")==0)                
    {                                      
        stream=NULL;                
        if((stream=fopen(path,"w"))==NULL) 
        {                                  
            perror("fopen write error");         
            exit(-1);                      
        }                                  
        return stream;                     
    }
 if(strcmp(mode,"a")==0)                
 {                                      
     stream=NULL;                
     if((stream=fopen(path,"a"))==NULL) 
     {                                  
         perror("fopen append error");         
         exit(-1);                      
     }                                  
 }                            

 if(strcmp(mode,"w+")==0)                
 {                                      
     stream=NULL;                
     if((stream=fopen(path,"w+"))==NULL) 
     {                                  
         perror("fopen read write error");         
         exit(-1);                      
     }                                  
 }
 return stream;
}

int Open_r(const char * path,int flags)
{
    int fd_in;
    fd_in=open(path,flags);
    if(fd_in<0)
    {
        perror("open error");
        exit(-1);
    }

    return fd_in;

}


int Open_w(const char * path,int flags,int mode)
{
    int fd_out;
    fd_out=open(path,flags,mode);
    if(fd_out<0)
    {
        perror("open error");
        exit(-1);
    }

    return fd_out;

}

ssize_t readn(int file,void * buf,size_t nbytes)
{
    char * buffer=(char *)buf;
    ssize_t total = nbytes;
    ssize_t numread=0;

    
    
    while(total>0)
    {
        if((numread=read(file,buffer,nbytes))<0)
        {
            perror("read error");
            exit(-1);
        }else if(numread==0)
        {
            break;//eof
        }
        total-=numread;
        buffer+=numread;


    }

    return total-numread;
}


ssize_t writen(int file,void * buf,size_t nbytes)
{
    const char * buffer =(const char*) buf;
    ssize_t numwrite;
    size_t total = nbytes;

    while(total>0)
    {
        if((numwrite=write(file,buffer,total))<=0)
        {
            perror("write error");
            exit(-1);
        }else{
            total-=numwrite;
            buffer+=numwrite;
        }
    }
    return nbytes;

}


ssize_t readline(int file,void * buf,size_t nbytes)
{



}




