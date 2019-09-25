#include <stdio.h>
#include <errno.h>
#include <pwd.h>
#include <ctype.h>
#include <stdlib.h>
#include <shadow.h>
#include <unistd.h>
#include <limits.h>
#include <shadow.h>
#include <string.h>
#define _BSD_SOURCE  //getpass()
#define _XOPEN_SOURCE //crypt()






/*scan whole pwd file*/

void scan_pwd()
{
    struct  passwd * pwd;

    while((pwd=getpwent())!=NULL)
    {
        printf("%-8s %5ld\n",pwd->pw_name,(long) pwd->pw_uid);
    }

    endpwent();//this function must be called ,allowing next getpwent()
    //setpwent()   back to the start of pwd file
    
}

/* from shadow file */
/*to use DES char * crypt() add -lcrpty link the crypt lib 
 *denote that crypt() is not invertible
 *to verify you should call crypt again and match 
 */

extern int errno;

int main(int argc,char ** argv)
{
    char * username ,*password,*encrypted,*p;
    struct passwd * pwd;
    struct spwd * spwd;
    int autoOk;
    size_t len;
    long lnmax;
    lnmax = sysconf(_SC_LOGIN_NAME_MAX);
    if(lnmax == -1)
    {
        lnmax = 256;
    }

    username = (char *) malloc(lnmax);
    if(username == NULL)
    {
        perror("malloc()");
        exit(0);
    }

    printf("Username: ");
    fflush(stdout);
    if(fgets(username,lnmax,stdin)==NULL)
    {
        fprintf(stdout,"eof");
        exit(0);
    }

    len = strlen(username);
    if(username[len-1]=='\n')
    {
        username[len-1]='\0';
    }

    pwd= getpwnam(username);
    if(pwd == NULL)
    {
        fprintf(stderr,"could not get password record");
        //exit(0);
    }

    spwd = getspnam(username);
    if(spwd == NULL && errno == EACCES)
    {
        fprintf(stderr,"no permission for accessing shadow file");
        exit(0);
    }

    if(spwd!=NULL)
    {
        pwd->pw_passwd = spwd->sp_pwdp;
    }

    password = getpass("Password: ");
    

    //excrypt password and clear out the visible info  
    encrypted = crypt(password,pwd->pw_passwd);
    for(p = password;*p!='\0';)
    {
        *p++ = '\0';
    }




    if(encrypted == NULL)
    {
        fprintf(stderr,pwd->pw_passwd);
        exit(0);
    }


    autoOk = strcmp(encrypted,pwd->pw_passwd);
    if(autoOk!=0)
    {
        printf("incorrect password\n");
        exit(0);
    }

    printf("successful authenticated : UID = %ld\n",(long) pwd->pw_uid);

    exit(0);













    printf("Hello world\n");
    return 0;
}

