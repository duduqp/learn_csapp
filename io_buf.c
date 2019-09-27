#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 1024
static char buf[BUF_SIZE];
int main()
{
    int r= setvbuf(stdout,buf,_IOFBF,BUF_SIZE);
    if(r!=0)
    {
        //note that not a -1 will return but a arbitrary non-zero
        //and no errno will be set
        fprintf(stdout,"setvbuf");
        exit(1);
    }
    printf("Hello");//without fflush \n

   // int c = getchar();//will stdout output because each stdio in will fflush stdout
    int c;
    while((c=getchar()!=0)){
        printf("%c",c);
    }
    
    return 0;
}

