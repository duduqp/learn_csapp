#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//access extern env-var
//1st method
/*extern char ** environ;

int main(int argc,char ** argv)
{
    char ** ep;
    for(ep = environ ;*ep!=NULL;ep++)
    {
        puts(*ep);
    }
    return 0;
}
*/

int main(int argc,char ** argv,char **envp)
{
    char ** ep;
    /*
     for(ep = envp ;*ep!=NULL;ep++)
    {
        puts(*ep);
    }*/

    //(not const!)char * getenv(char * name)
    char * shell = getenv("SHELL");
    puts(shell);

    //add an env-var,also make sense for child processes
    //string format : name=value
    //just let it be pointed but not copied,hence static 
    static char global_msg[12]="DATE=MONDAY";
    /*int res = putenv(global_msg);
    if(res!=0)//note not a -1 error but a non-zero
    {
        printf("error when add an env-var");
        exit(0);
    }*/

    //printf("now visit env-var DATE:%s",getenv("DATE"));
    



    //setenv() unsetenv() would be more convenient
    //return -1 on error
    //never add a "=" ,setenv will do it for you
    int res = setenv("DATE","TUESDAY",1);// 1 != 0 means override existed one
    if(res==-1)
    {
        printf("error setenv()");
        exit(0);
    }
    printf("now visit env-var DATE after setenv:%s",getenv("DATE"));
    exit(0);

}
















