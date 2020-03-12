#include <stdio.h>
#include <unp.h>

char BigCase(char c){
    return c-('a'-'A');
}
#define MAX_SIZE 64
//protocol free style
void child_process(int fd){
    char outbuf[MAX_SIZE];
    int cur_index=0;
    char recvd;
    
    while(1){
        ssize_t recvresult;
        if(recvresult=(recv(fd,&recvd,1,0))<0){
           perror("recv error");
           exit(-1);
        }else if(recvresult==0){
            break;
        }
        //full?
        if(cur_index<MAX_SIZE){
            outbuf[cur_index++]=BigCase(recvd);
        }else{
            char *msg="already full";
            send(fd,msg,strlen(msg),0);
            recvd='\n';
            continue;
        }

        if(recvd=='\n'){
            send(fd,outbuf,cur_index,0);
            cur_index=0;
            continue;
        }
    }

}

static void sig_hdr(int signo){
    while(waitpid(-1,0,WNOHANG)>0);
    return ;
}

int main()
{
    

    printf("Hello world\n");
    return 0;
}

