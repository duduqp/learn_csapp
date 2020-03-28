#pragma once
#include <sys/epoll.h>
#include <functional>
#include <memory>
#include <string>
#include <map>
#include "timer.h"
#include "RequestContent.h"

class EventLoop;
class RequestContent;

class Event
{
    typedef std::function<void()> CallBack;
public:
    Event(EventLoop *,int fd) ;
    Event(EventLoop *);
    ~Event();
    
    void Setfd(int fd_);
    void SetHolder(std::shared_ptr<RequestContent> holder_);
    void SetReadHandler(CallBack  cb){ Read_Handler=cb; }
    void SetWriteHandler(CallBack  cb){ Write_Handler=cb; }
    void SetErrorHandler(CallBack  cb){ Error_Handler=cb; }
    void SetConnectionHandler(CallBack  cb){ Connection_Handler=cb; }


    void HandleEvent(){
        event_type=0;
        if((revent_type&EPOLLHUP)&&!(revent_type&EPOLLIN))
        {
            event_type=0;return;
        }
        if(revent_type & EPOLLERR)
        {
            if(Error_Handler) Error_Handler();
            event_type=0;return ;
        }
        if(revent_type&(EPOLLIN|EPOLLPRI|EPOLLRDHUP))
        {
            HandleRead();
        }
        if(revent_type&EPOLLOUT)
        {
            HandleWrite();
        }
        HandleConnection();
    }


    void HandleRead();
    void HandleWrite();
    void HandleConnection();
    void HandleError(int fd,int err_no,const std::string & msg);
    bool UpdateLastEvent(){
        bool ret=(last_event_type==event_type);
        last_event_type=event_type;
        return ret;
    }

    int GetEventType()  {return event_type;}
    int Getfd() const{ return fd;}
    int GetLastEvent() const{ return last_event_type; }
    std::shared_ptr<RequestContent> GetHolder() const{ return Holder.lock(); }

    void SetEventType(int event_type_)
    {
        event_type=event_type_;
    }
    void SetREventType(int ret_event_type)
    {
        revent_type=ret_event_type;
    }




private:
    EventLoop * Loop;
    int fd;
    int event_type;
    int revent_type;
    int last_event_type;

    std::weak_ptr<RequestContent> Holder;
    int Parse_URI();
    int Parse_Headers();
    int AnalysisRequest();

    CallBack Read_Handler;
    CallBack Write_Handler;
    CallBack Error_Handler;
    CallBack Connection_Handler;
        

};

