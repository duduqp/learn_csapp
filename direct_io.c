#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(int argc,char ** argv)
{
    int fd;
    ssize_t numrd;
    size_t len,align;
    off_t ofs;
    void * buf;

    //check arg 
    if(argc<3||strcmp(argv[1],"--help")==0)// if cmd gives direct_io --help then we give a description 
    {
        fprintf(stdout,"direct_io file len [offset [alignment]]");
        exit(0);
    }

    


        
}
