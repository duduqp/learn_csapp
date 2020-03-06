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

//buffered version
ssize_t read_msg(int fd,char * to,size_t target_length){
    ssize_t read_count=0;
    size_t nread=target_length;

    int msglen,msgtype;
    if((read_count=readn(fd,&msglen,sizeof(msglen)))!=sizeof(msglen)){
        //even not guarantee?!
        return min(read_count,0);
    }

    msglen=ntohl(msglen);
    //parse the length 
    read_count=readn(fd,to,target_length);
    if(read_count<=0){
        return min(read_count,0);
    }

    return read_count;

}


ssize_t parsemsg(int fd,char * to,char end){
    //use end as seperator
    //todo
    return 0;
}

static int count;
static void sig_hdr(int signo){
     
    printf("received : %d DataGrams\n",count);
    exit(0);//ignore rest procedure
}
int main()
{
    signal(SIGINT,&sig_hdr);

    int lfd=Socket(AF_INET,SOCK_STREAM,0);
    char  buf[4096];


    struct sockaddr_in serv_addr,conn_addr;
    socklen_t conn_len=sizeof(conn_addr);
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(8888);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    
    int on=1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

    bind(lfd,(struct sockaddr *)&serv_addr,conn_len);
    listen(lfd,128);

    int connfd;
    connfd=Accept(lfd,(struct sockaddr *)&conn_addr,&conn_len);

    while(1){
        int n=read_msg(connfd,buf,sizeof(buf));
        if(n==0){
            break;//EOF
        }else if(n<0){
            if(errno==EINTR){
                continue;
            }else{
                break;
            }
        }else{
            buf[n]='\0';
            count++;
        }
    }

    printf("total received:%d \n",count);
    return 0;
}

