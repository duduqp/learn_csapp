#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#define MAXN 1024

int main(int argc,char **argv)
{
    int in_fd,o_fd,o_flags;
    mode_t f_perm;
    ssize_t n_rd;
    char buf[MAXN];

    //check cmd parm
    if(argc!=3 || strcmp(argv[1],"--help")==0 )
    {
        fprintf(stderr,"%s old-file new-file\n",argv[0]);
        exit(0);
    }
    
    /*open input file and output file*/
    in_fd = open(argv[1],O_RDONLY);
    /*check error*/
    if(in_fd == -1)
    {
        perror("open()");
        exit(0);//close all fd auto
    }
    
    //set mode and flags
    o_flags = O_CREAT | O_WRONLY | O_TRUNC;
    //if not exists,create ,if exists truncate it
    //set file permissions rw-rw-rw-
    f_perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    o_fd = open(argv[2],o_flags,f_perm);
    if(o_fd == -1)
    {
        perror("open()");
        exit(0);
    }

    /*trans data*/
    
    //while loop check if read target number--MAXN
    while((n_rd=read(in_fd,buf,MAXN))>0)
    {
        if(write(o_fd,buf,n_rd)!=n_rd)
        {
            perror("wirte()");
            exit(0);
        }
    }

    //not even once
    if(n_rd == -1)
    {
        perror("read()");
        exit(0);
    }


    //succ
    if(close(in_fd)==-1)
    {
        perror("close()");
        exit(0);
    }

    if(close(o_fd)==-1)
    {
        perror("close()");
        exit(0);
    }

    exit(1);
}

