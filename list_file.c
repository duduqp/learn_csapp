#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

extern int errno;
static void listfile(const char * dirpath)
{
    DIR * dirp;
    struct dirent * dp;
    int iscurrent;

    iscurrent = (strcmp(dirpath,".") == 0);

    dirp = opendir(dirpath);
    if(dirp == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    //for each entry
    
    for(;;)
    {
        errno =0;
        dp = readdir(dirp);
        if(dp ==NULL)
        {
            //last entry
            break;
        }

        if(strcmp(dp->d_name,".")==0||strcmp(dp->d_name,"..")==0)
        {
            // if read     .   .. 
            continue;
        }

        if(iscurrent!=0)
        {
            printf("%s/",dirpath);
        }
        printf("%s\n",dp->d_name);
    }

    if(errno!=0)
    {
        perror("readdir");
        exit(EXIT_FAILURE);
    }

    if(closedir(dirp) == -1)
    {
        perror("closedir");
        exit(EXIT_FAILURE);
    }
}


int main(int argc,char ** argv)
{
    if(argc >1 && strcmp(argv[1],"--help")==0)
    {
        fprintf(stderr,"%s [dir .. ] \n",argv[0]);
    }

    if(argc == 1)
    {
        listfile(".");
    }
    else{
        for(argv++;*argv;argv++)
        {
            listfile(*argv);
        }

    }
        exit(EXIT_SUCCESS);
}

