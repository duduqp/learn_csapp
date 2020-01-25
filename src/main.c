#include <stdio.h>
#include "../header/wrap.h"
#include <stdlib.h>
#define BUFSIZE 4096

int main()
{
    FILE * ros = fopen("wrap.c","r");
    if(ros==NULL)
    {
        perror("rdonly open ");
        exit(-1);
    }

    
     FILE * wraped = Fopen("wrapedstdout","w");
     fprintf(wraped,"wrapped fprintf \n");
    return 0; 


    FILE * wos = fopen("stdio.out","w");
    if(ros==NULL)
    {
        perror("wtonly open ");
        exit(-1);
    }


    int num=0;
    if((num=fprintf(wos,"first wirte use write only stdstream\n"))<0)
    {
        perror("fprintf");
        exit(-1);
     }

    fclose(wos);
    fclose(ros);


    printf("operation finish\n");
    return 0;
}

