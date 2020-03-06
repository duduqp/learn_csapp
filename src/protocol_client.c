#include <stdio.h>
#include <unp.h>

struct mymsg{
    int msglen;
    int msgtype;
    char msg[4096];
};
ssize_t readn(int fd,void * to,size_t target_length)
{
    char * buf=(char *)to;//convert 
    size_t nread=target_length;

    int count = 0;
    while(nread>0){
        if((count=read(fd,buf,nread))<0){
            if(errno==EAGAIN||errno==EINTR){
                continue;
            }
            return -1;//truely error
        }else if(count ==0){
            //EOF
            break;
        }else{
            buf+=count;
            nread-=count;
        }
    }
    return (target_length-nread);
}


int main()
{


    return 0;
}

