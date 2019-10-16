#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void printsigset(FILE * of,const char * prefix,const sigset_t *sigset);
int printsigmask(FILE * of,const char *msg);
int printpendingsigs(FILE *of,const char *msg);

