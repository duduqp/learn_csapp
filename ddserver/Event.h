#pragma once
#include <sys/epoll.h>
#include <functional>
#include <memory>
#include <string>
#include <map>
#include "Timer.h"
#include "RequestContent.h"

class EventLoop;
class RequestContent;

class Event
{
    typedef std::function<void()> CallBack;
public:
    Event(EventLoop * loop_,int fd_):Loop(loop_),fd(fd_),event_type(0),last_event_type(0){} 
    Event(EventLoop * loop_):Loop(loop_),fd(0),event_type(0),last_event_type(0){}
    ~Event(){}
    
    void Setfd(int fd_){ fd=fd_; }
    void SetHolder(std::shared_ptr<RequestContent> holder_){ Holder=holder_; }
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


    void HandleRead(){ if(Read_Handler) Read_Handler(); }
    void HandleWrite(){ if(Write_Handler) Write_Handler(); }
    void HandleConnection(){ if(Connection_Handler) Connection_Handler(); }
  //  void HandleError(int fd,int err_no,const std::string & msg);
    bool UpdateLastEvent(){
        bool ret=(last_event_type==event_type);
        last_event_type=event_type;
        return ret;
    }

    int &GetEventType()  {return this->event_type;}
    int Getfd() const{ return fd;}
    int GetLastEvent() { return this->last_event_type; }
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
   /* int Parse_URI();
    int Parse_Headers();
    int AnalysisRequest();*/
    CallBack Read_Handler;
    CallBack Write_Handler;
    CallBack Error_Handler;
    CallBack Connection_Handler;
        

};

