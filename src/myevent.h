#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>


struct event_loop{

    int quit;
    struct event_dispatcher * evt_dispacher;
    
    void *event_dispatcher_data;
    struct channel_map * channelmap;


    int is_handle_pending;
    struct channel_element * pending_head;
    struct channel_element * pending_tail;

    pthread_t owner_thread_id;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int sockpair[2];
    char * thread_name;
};

int event_loop_run(event_loop * evt_loop){
    assert(evt_loop!=NULL);

    struct event_dispatcher * dispatcher=evt_loop->evt_dispacher;

    if(evt_loop->owner_thread_id!=pthread_self())
    {
        exit(-1);
    }

    //same as log
    printf("event_loop running...,%s",evt_loop->thread_name);


    struct timeval tv;
    tv.tv_sec=1;

    while(!evt_loop->quit)
    {
        //block wait io evt
        dispatcher->dispatch(evt_loop,&timeval);//select epoll...

        //handle pending channel
        evt_loop_handle_running_channel(evt_loop);

    }

    //log
    printf("event_loop end,%s",evt_loop->thread_name);
    return 0;
}



struct event_dispatcher{
    const char * name;

    void (*init)(struct event_loop * evt_loop);//register event_loop
    int (*add)(struct event_loop * evt_loop,struct channel * c);
    int (*del)(struct event_loop * evt_loop,struct channel * c);
    int (*update)(struct event_loop * evt_loop,struct channel * c);

    int (*dispatch)(struct event_loop * evt_loop,struct timeval * tv);

    void (*clear)(struct event_loop * evt_loop);

};

typedef  int (*evt_callback)(void * data);

struct channel {
    int fd;
    int events;

    event_read_callback evtReadCallback;
    event_write_callback evtWriteCallback;

    void *data;//callback data 
};//wrap a event and its corresponding call back function

struct channel_map{
    void **entry;
    int entry_num;
};

int channel_event_activate(struct event_loop * evt_loop,int fd,int revt)
{
    struct channel_map * map=evt_loop->channelmap;
    //log
    printf("activate channel fd == %d,revt=%d,%s",fd,revt,evt_loop->thread_name);

    if(fd<0)
    {
        return 0;
    }

    if(fd>=map->entry_num)
    {
        return -1;
    }

    struct channel * chn = (struct channel *)map->entry[fd];
    assert(fd==chn->fd);

    if(revt & EVENT_READ){
        if(chn->evtReadCallback!=NULL) chn->evtReadCallback(chn->data);
    }

    if(revt & EVENT_WRITE){
        if(chn->evtWriteCallback!=NULL) chn->evtWriteCallback(chn->data);
    }

    return 0;
}


