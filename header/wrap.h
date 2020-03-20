#ifndef __WRAP_H_
#define __WRAP_H_
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
int Socket(int domain,int type,int protocol);
int Bind(int lisfd,const struct sockaddr * addr,socklen_t addrsize);
int Connect(int clifd,const struct sockaddr * addr,socklen_t addsize);
int Listen(int fd,int backlog);
int Accept(int lisfd,struct sockaddr * servaddr,socklen_t * addrsize);
int Open_r(const char * path,int flags);
int Open_w(const char * path,int flags,int mode);
FILE * Fopen(const char * path,const char * mode);
ssize_t readn(int file,void * buf,size_t nbytes);
ssize_t writen(int file,void * buf,size_t nbytes);
ssize_t readline(int file,void * buf,size_t nbytes);

#endif
