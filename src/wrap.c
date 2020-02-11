#include <stdio.h>
#include "../header/wrap.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
void perror_exit(const char * msg,int code)
{
    perror(msg);
    exit(code);
}


int Socket(int domain,int type,int protocol)
{
    int sock = socket(domain,type,protocol);
    if(sock < 0)
    {
        perror_exit("socket",-1);
    }
    return sock;
}
int Bind(int lisfd,const struct sockaddr * addr,socklen_t addrsize)
{
    if(bind(lisfd,addr,addrsize)<0)
    {
        perror_exit("bind",-1);
    }
    return 0;
}
int Connect(int clifd,const struct sockaddr * addr,socklen_t addsize)
{
    if(connect(clifd,addr,addsize)<0)
    {
        perror_exit("connect",-1);
    }
    return 0;
}
int Listen(int fd,int backlog)
{
    if(listen(fd,(backlog<=128?backlog:128))<0)
    {
        perror_exit("listen",-1);
    }
    return 0;


}
int Accept(int lisfd,struct sockaddr * cliaddr,socklen_t * addrsize)
{
    int con_fd;
    if((con_fd=accept(lisfd,cliaddr,addrsize))<0)
    {
        perror_exit("accept",-1);
    }
    return con_fd;
}



int Open_r(const char * path,int flags)
{
    int rdfd;
    if((rdfd=open(path,flags))<0)
    {
        perror_exit("open",-1);
    }
    return rdfd;
}
int Open_w(const char * path,int flags,int mode)
{
    int wrfd;
    if((wrfd=open(path,flags,mode))<0)
    {
        perror_exit("open",-1);
    }

    return wrfd;

}

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




