#ifndef __WRAP_H_
#define __WRAP_H_
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
int Open_r(const char * path,int flags);
int Open_w(const char * path,int flags,int mode);
FILE * Fopen(const char * path,const char * mode);
#endif
