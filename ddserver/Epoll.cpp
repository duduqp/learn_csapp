#include <iostream>
#include <assert.h>
#include <errno.h>
#include <cstring>
#include <deque>
#include <sys/socket.h>
#include <sys/epoll.h>
#include "util.h"
#include "Logger.h"
#include "Epoll.h"

#include <arpa/inet.h>
using namespace std;

const int EVENTNUM=4096;
const int EPOLLWAIT_TIME=10000;//ms

typedef shared_ptr<Event> ptr_Event;

Epoll::Epoll():epoll_base(epoll_create1(EPOLL_CLOEXEC)),events(EVENTNUM)
{
    assert(epoll_base>0);
}

Epoll::~Epoll(){}

//register new fd
void Epoll::Epoll_Add(ptr_Event req,int timeout_msecs)
{
    std::cout << __func__<<std::endl;
    int fd=req->Getfd();
    std::cout << "add event fd:"<<fd <<"timout:"<<timeout_msecs<<std::endl;
    if(timeout_msecs>0)
    {
        Add_Timer(req,timeout_msecs);
        fd2RequestContent[fd]=req->GetHolder();
    }
    struct epoll_event event;
    event.data.fd=fd;
    event.events=req->GetEventType();
    
    req->UpdateLastEvent();

    fd2Event[fd]=req;
    if(epoll_ctl(epoll_base,EPOLL_CTL_ADD,fd,&event)<0)
    {
        LOG << "Epoll_Add Error#";
        fd2Event[fd].reset();
    }
    std::cout << "after epoll add "<<std::endl;
}

//modify fd status
void Epoll::Epoll_Mod(ptr_Event req,int timeout_msecs){
    std::cout << __func__<<std::endl;
    if(timeout_msecs>0) Add_Timer(req,timeout_msecs);
    int fd=req->Getfd();
    if(!req->UpdateLastEvent()){
        struct epoll_event event;
        event.data.fd=fd;
        event.events=req->GetEventType();
        if(epoll_ctl(epoll_base,EPOLL_CTL_MOD,fd,&event)<0)
        {
            LOG << "Epoll_Mod Error#";
            fd2Event[fd].reset();
        }
    }
}

void Epoll::Epoll_Delete(ptr_Event req)
{
    std::cout << __func__<<std::endl;
    int fd=req->Getfd();
    struct epoll_event event;
    event.data.fd=fd;
    event.events=req->GetLastEvent();
    if(epoll_ctl(epoll_base,EPOLL_CTL_DEL,fd,&event)<0)
    {
        LOG<<"Epoll_Del Error#";
    }
    fd2Event[fd].reset();
    fd2RequestContent[fd].reset();
}


std::vector<ptr_Event> Epoll::Poll()
{
    std::cout << __func__<<std::endl;
    while(true){
        std::cout <<"events size:"<< events.size() <<std::endl;
        int event_count=epoll_wait(epoll_base,&*events.begin(),events.size(),EPOLLWAIT_TIME);
        if(event_count<0) LOG<<"Epoll_Wait Error#";
        std::cout << "eventreturned count:"<<event_count<<std::endl;
        std::vector<ptr_Event> req_data=GetEventRequest(event_count);
        std::cout << "req_data size"<<req_data.size()<<std::endl;
        if(req_data.size()>0) return req_data;
    }

}


void Epoll::HandleExpired(){
    timer.Handle_Expired();
    std::cout << __func__<<std::endl;
}

std::vector<ptr_Event> Epoll::GetEventRequest(int num)
{
    std::cout << "Epoll "<<__FILE__<<__LINE__<<std::endl;
    std::vector<ptr_Event> ret_data;

    for(int i=0;i<num;++i)
    {
        int fd=events[i].data.fd;
        ptr_Event cur_evt=fd2Event[fd];

        if(cur_evt){
            cur_evt->SetEventType(0);
            cur_evt->SetREventType(events[i].events);//returned eventtype
            ret_data.push_back(cur_evt);
        }else{
            LOG<<"Cur Event Invalid#";
        }
    }
    return ret_data;
}

void Epoll::Add_Timer(ptr_Event req,int timeout_msecs)
{
    std::cout << "epoll addtimer"<<std::endl;
    std::shared_ptr<RequestContent> content=req->GetHolder();
    if(!content) LOG<<"Add_Timer Error#";
    timer.AddTimeNode(content,timeout_msecs);
}








