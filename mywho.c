#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <utmp.h>
void show_info(void * u_rd)
{
    struct utmp * tmp = (struct utmp *) u_rd;
    printf("%s\n",tmp->ut_user);
    printf("%d\n ",tmp->ut_pid);
}

int main(int argc,char ** argv)
{
    struct utmp tmp_record;
    int u_fd;
    int st_size = sizeof(struct utmp);

    if((u_fd=open(UTMP_FILE,O_RDONLY))== -1){
        perror("open error");
        exit(1);
    }else{
        while(read(u_fd,&tmp_record,st_size)!=0){
            show_info(&tmp_record);
        }
        close(u_fd);
        exit(0);
    }
}

