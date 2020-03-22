#pragma once
#include <stdlib.h>
#include <string>

ssize_t readn(int fd,void * buf,size_t n); 
ssize_t readn(int fd,std::string & inbuffer); 
ssize_t writen(int fd,void * buf,size_t n); 
ssize_t writen(int fd,std::string & outbuffer); 


void sig_hdr(int signo);
