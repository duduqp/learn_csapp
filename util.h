#pragma once
#include <stdlib.h>
#include <string>
const int MAX_BUF = 4096;
ssize_t readn(int fd,void * buf,size_t n); 
ssize_t readn(int fd,std::string & inbuffer);
ssize_t readn(int fd,std::string & inbuffer,bool & zero);
ssize_t writen(int fd,void * buf,size_t n); 
ssize_t writen(int fd,std::string & outbuffer); 
ssize_t readline(int fd,void * buf,size_t maxline);
ssize_t writeline(int fd,void * buf,size_t maxline);
ssize_t peekline(int fd,void * buf,char sep='\n');
ssize_t peekn(int fd,void * buf,size_t n);
ssize_t readblock(int fd,void * buf,int blksize,char sep);
void Default_Error_Handler();
void SignalHandler_PIPE();
void SetSocketOpt_NonLinger(int fd);
void SetSocketOpt_NonDelay(int fd);
void SetSocketOpt_NonBlock(int fd);
void ShutDownWR(int fd);
void ShutDownW(int fd);
void ShutDownR(int fd);
int Socket_Bind_Listen(short port);

