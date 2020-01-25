#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
int main()
{

    struct stat s;
    if((stat("/home/ddqp/csapp/account.c",&s)!=0))
    {
        perror("stat error");
        exit(1);
    }

    if(S_ISREG(s.st_mode))
    {
        fprintf(stdout,"is regular file");
    }else if(S_ISDIR(s.st_mode))
    {
        fprintf(stdout,"is directory");
    }else if(S_ISCHR(s.st_mode))
    {
        fprintf(stdout,"is char file");
    }else if(S_ISBLK(s.st_mode))
    {
        fprintf(stdout,"is blk file");
    }
    else if(S_ISLNK(s.st_mode))
    {
        fprintf(stdout,"is link");
    }
    else if(S_ISSOCK(s.st_mode))
    {
        fprintf(stdout,"is socket");
    }



    if(stat("symlink",&s)<0)
    {
        perror("stat error");
        exit(1);
    }
    
    fprintf(stdout,"symbol's uid:%d\n",s.st_uid);
    if(S_ISLNK(s.st_mode))
    {
        fprintf(stdout,"symbolnk is a symbol link file\n");
    }

    char buf[4096];
    /*int fd=open("./symlink",O_RDONLY);
    if(fd<0)
    {
        perror("open error");
        exit(1);
    }else{
        int n = read(fd,buf,4096);
        buf[n]='\0';
        fprintf(stdout,"%s",buf);
    }*/

//open will follow symbol link
//to display symbol link itselg use readlink
    int n = 0; 
    if((n=readlink("./symlink",buf,4096))>0)
    {
        buf[n]='\0';
        fprintf(stdout,"%s",buf);
    }


    return 0;
}

