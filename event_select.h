#pragma once
#include "netprogramming.h"
#include <functional>
#include <list>
int event_select(int maxfd,fd_set readset,fd_set writeset,fd_set expset);

uint32_t set_timeout(void (*handler)(void *),void * arg,int ms);

void cancel_timeout(uint32_t timerid);

typedef struct event_type event_type;

struct event_type{
    event_type * next;
    struct timeval timev;
    uint32_t timerid;
    std::function<void(void *)> handler ;
    void * arg;
};

static std::list<event_type> active_event;
static std::list<event_type> idle_event;


static event_type * allocate_timer(void){

}
