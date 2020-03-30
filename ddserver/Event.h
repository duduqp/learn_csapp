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
public:
    typedef std::function<void()> CallBack;
    Event(EventLoop * loop_,int fd_):Loop(loop_),fd(fd_),event_type(0),last_event_type(0){} 
    Event(EventLoop * loop_):Loop(loop_),fd(0),event_type(0),last_event_type(0){}
    ~Event(){}
    
    void Setfd(int fd_){ fd=fd_; }
    void SetHolder(std::shared_ptr<RequestContent> holder_){ Holder=holder_; }
    void SetReadHandler(CallBack && cb){ Read_Handler=cb; }
    void SetWriteHandler(CallBack && cb){ Write_Handler=cb; }
    void SetErrorHandler(CallBack &&  cb){ Error_Handler=cb; }
    void SetConnectionHandler(CallBack && cb){ Connection_Handler=cb; }


    void HandleEvent(){

    std::cout << __func__<<std::endl;
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
            std::cout << "HandleEVENT find call handle read"<<std::endl;
            HandleRead();
        }
        if(revent_type&EPOLLOUT)
        {
            HandleWrite();
        }
        std::cout << "HandleEVENT find call handleconnection"<<std::endl;
        HandleConnection();
    }


    void HandleRead(){
        std::cout << __func__<<std::endl;
        if(Read_Handler==nullptr)
        {
            std::cout << "Read Handler empty!"<<std::endl;
        }
        if(Read_Handler) Read_Handler(); }
    void HandleWrite(){ if(Write_Handler) Write_Handler(); }
    void HandleConnection(){
        std::cout << __func__<<std::endl;
        if(Connection_Handler) Connection_Handler(); }
  //  void HandleError(int fd,int err_no,const std::string & msg);
    bool UpdateLastEvent(){
        bool ret=(last_event_type==event_type);
        last_event_type=event_type;
        return ret;
    }

    uint32_t &GetEventType()  {return this->event_type;}
    uint32_t Getfd() const{ return fd;}
    uint32_t GetLastEvent() { return this->last_event_type; }
    std::shared_ptr<RequestContent> GetHolder() const{ return Holder.lock(); }

    void SetEventType(uint32_t event_type_)
    {
        event_type=event_type_;
    }
    void SetREventType(uint32_t ret_event_type)
    {
        revent_type=ret_event_type;
    }




private:
    EventLoop * Loop;
    int fd;
    uint32_t event_type;
    uint32_t revent_type;
    uint32_t last_event_type;

    std::weak_ptr<RequestContent> Holder;
   /* int Parse_URI();
    int Parse_Headers();
    int AnalysisRequest();*/
    CallBack Read_Handler;
    CallBack Write_Handler;
    CallBack Error_Handler;
    CallBack Connection_Handler;
        

};

