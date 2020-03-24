#pragma once
#include <stdlib.h>
#include <string>

ssize_t readn(int fd,void * buf,size_t n); 
ssize_t readn(int fd,std::string & inbuffer); 
ssize_t writen(int fd,void * buf,size_t n); 
ssize_t writen(int fd,std::string & outbuffer); 
ssize_t readline(int fd,void * buf,size_t maxline);
ssize_t writeline(int fd,void * buf,size_t maxline);
void Default_Error_Handler();
void sig_hdr(int signo);
