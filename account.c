#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

int main()
{
    struct passwd *pwd;
    pwd = getpwnam("ddqp");
    
    char * pwd_pw_name = pwd->pw_name;
    fprintf(stdout,"ddqp's passwd name : %s",pwd_pw_name);

    int  errno = 0;
    pwd = getpwnam("ddqp");
    if(pwd == NULL)
    {
        if(errno == 0)
        {
            fprintf(stderr,"not found");
            exit(0);
        }
        else{
         
            fprintf(stderr,"error");
            perror("getwname");
            exit(0);
        }
   

    }
    char * pwd_pw_pwd = pwd->pw_passwd;
    fprintf(stdout,"ddqp's passwd crypted passwd: %s ",pwd_pw_pwd);

}

