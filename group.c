#include <stdio.h>
#include <grp.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>;
char * usrnamefromuid(uid_t uid)
{
    strcu
}
int main()
{
    errno =0;
    struct group * p_grp = getgrnam("ddqp");
    if(p_grp ==NULL)
    {
        if(errno == 0)
        {
            printf("not found");
            exit(0);
        }else{
            perror("getgrpname");
            exit(0);
        }
    }
    char * p_grpname = p_grp->gr_name;
    fprintf(stdout,"ddqp's group name %s",p_grpname);
    exit(0);
}

