#include <iostream>
#include "packet.h"
#include "netprogramming.h"

int main(int argc,char ** argv)
{   
    int listenfd=Socket_Bind_Listen(9999);
    fd_set allset,read_set;
    packet keepalive_packet;
    int count=sizeof(keepalive_packet);
    int heartbeat=0;
    struct timeval timev;
    int retcount;

    struct sockaddr_in client_addr;
    socklen_t client_addr_len=sizeof(client_addr);
    int connfd=accept(listenfd,(struct sockaddr *)&client_addr,&client_addr_len);
    timev.tv_sec=A_TIMEOUT;
    for(;;)
    {
        retcount=select(connfd,)
    }

        

    return 0;
}
