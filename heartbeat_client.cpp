#include <iostream>
#include "packet.h"
#include "efficient_tcp.h"
#include "ddserver/util.h"
#include <sys/select.h>
#include <ctime>

int main()
{
    fd_set allset;
    fd_set read_set;
    struct timeval timev;
    int client_fd=socket(AF_INET,SOCK_STREAM,0);
    int heartbeat=0;
    int retn;
    packet keepalive_packet;
    int count=sizeof(keepalive_packet);

    FD_ZERO(&allset);
    FD_SET(client_fd,&allset);
    timev.tv_sec=A_TIMEOUT;
    timev.tv_usec=0;
    for(;;){
        read_set=allset;
        retn=select(client_fd+1,&read_set,NULL,NULL,&timev);
        if(retn<0)
        {
            perror("select error");
            exit(-1);
        }else if(retn==0)
        {   
            //timeout 
            if(++heartbeat>3)//heartbeat expired
            {
                perror("remote dead");
                exit(-1);
            }
            keepalive_packet.state=MSG_TYPE_HEARTBEAT;
            int ret=send(client_fd,(char *)&keepalive_packet,sizeof(keepalive_packet),0);
            if(ret<0)
            {
                perror("send error");
                exit(-1);
            }

            timev.tv_sec=B_TIMEOUT;
            continue;
        }else{
            //handle
            if(!FD_ISSET(client_fd,&read_set))
            {
                perror("not a valid sockfd returned");
                exit(-1);
            }
            int ret=recv(client_fd,(char *)&keepalive_packet+sizeof(keepalive_packet)-count,count,0);
            if(ret<0)
            {
                perror("recv error");
                exit(-1);
            }else if(ret==0)
            {
                break;
            }
            heartbeat=0;
            timev.tv_sec=A_TIMEOUT;
            count-=ret;
            if(count==0)
            {
                count=sizeof(keepalive_packet);
            }
        }

    return 0;
    }
}
