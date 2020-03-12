#include <stdio.h>
#include <unp.h>
#define SERV_PORT 6666
int onConnectionCompleted(struct tcp_connection *tcp_connection)
{

}


int onMsg(struct buffer * input,struct tcp_connection ** tcpconn)
{

}


int onWriteCompleted(struct tcp_connection * tcpconn){

}

int onConnectionClosed(struct tcp_connection * tcpconn){

}

int main()
{
    //main thread event_loop served as a reactor
    struct event_loop * evt_loop=event_loop_init();


    //init acceptor
    struct acceptor * acpt=acceptor_init(SERV_PORT);
    
    //init tcp server
    struct tcp_server * tcpserv=tcp_server_init(event_loop,acpt,onConnectionCompleted,onConnectionClosed,onMsg,onWriteCompleted);
    
    tcp_server_start(tcpserv);

    event_loop_run(evt_loop);
    
    
    
    
    
    return 0;
}

