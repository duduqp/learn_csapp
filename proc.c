#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

int main()
{
    fprintf(stdout,"pid:%ld",(long) getpid());
    getchar();
    return 0;
}

