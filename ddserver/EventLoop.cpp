#include <iostream>
#include "Epoll.h"
#include "logger.h"
#include <sys/eventfd.h>
#include "util.h"

using namespace std;

__thread EventLoop * LocalThreadLoop=NULL;

int CreateEventfd(){
    int evtfd=eventfd(0,EFD_NONBLOCK|EFD_CLOEXEC);
    if(evtfd<0)
    {
        LOG<<"Failed in eventfd";
        abort();
    }
    return evtfd;
}

EventLoop::EventLoop():

