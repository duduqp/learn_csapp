#pragma once
#include <sys/epoll.h>
#include <memory>
#include <map>
#include <vector>
#include "Event.h"
#include "timer.h"
#include "RequestContent.h"


class Epoll
{
    
public:
    Epoll() {}
    ~Epoll() {}
    void Epoll_Add(std::shared_ptr<Event> event,int timeout_msecs);
    void Epoll_Mod(std::shared_ptr<Event> event,int timeout_msecs);
    void Epoll_Delete(std::shared_ptr<Event> event);
    std::vector<std::shared_ptr<Event>> Poll();
    std::vector<std::shared_ptr<Event>> GetEventRequest(int event_num);
    void Add_Timer(std::shared_ptr<Event> req,int timeout_msecs);
    int GetEpollBase(){return epoll_base;}
    void HandleExpired();
private:
    static const int Max_Epoll_Listen=100000;//per 1G 100000
    int epoll_base;
    std::vector<epoll_event> events;
    std::shared_ptr<Event> fd2Event[Max_Epoll_Listen];
    std::shared_ptr<RequestContent> fd2RequestContent[Max_Epoll_Listen];
    Timer timer;
};

