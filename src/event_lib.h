#pragma once
#define BUF_SIZE 4096
#define MAX_EVTS 128
//event_major
int epoll_base;//global epoll_base 
struct event_major{
    int fd;
    int event_trigger_type;//EPOLL_IN EPOLL_OUT EPOLL_ET
    char buf[BUF_SIZE];

    int base;//register epoll_base
    int isRegister;//1 for is registered to epoll_base 0 otherwise
    void (*event_hdr)(int fd,int event_trigger,void * args);//register callback handler
    void * hdr_args;//args for hdr
    int cursor;//cursor for buf

    //time 
    long long active_time;//timestramp ,update when registered into an epoll_base

};

//array for listen event set
struct event_major eventset[MAX_EVTS];

void event_set(struct event_major * obj,int fd,int event_trigger,
               void (*hdr)(int ,int ,void * ))
{
    //init a pass in ptr event
    obj->fd=fd;
    obj->
}



