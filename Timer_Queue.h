#pragma once
#include "Timer.h"
#include "TimerId.h"
#include "ddserver/Event.h"
#include <unordered_map>
#include <memory>
#include <utility>
#include <assert.h>


class TimerNode:Uncopyable
{
public:
    explicit TimerNode(std::unique_ptr<Timer> timerptr_,TimerNode * prev_=nullptr,TimerNode * post_=nullptr):
    timerptr(std::move(timerptr_)),prev(prev_),post(post_) {  
        if(prev)
        {
            prev->post=post_;
        }
        if(post)
        {
            post->prev=this;
        }
    }
    
    ~TimerNode(){
        if(prev)
        {
            prev->post=post;
        }
        if(post)
        {
            post->prev=prev;
        }
    }

private:
    std::unique_ptr<Timer> timerptr;
    TimerNode * prev;
    TimerNode * post;
};

typedef std::pair<int64_t,std::unique_ptr<TimerNode> > HashEntry;//expiration time --- ptr
typedef TimerNode*  orderd_timerlist;


class Timer_Queue:Uncopyable
{
public:
    Timer_Queue() :timerid(){ header = new TimerNode(std::make_unique<Timer>(0.0,Now(),std::function<void()>())); }
    ~Timer_Queue() { assert(header!=nullptr);delete header ;}




private:
    //fast query
    //fast delete
    //auto link
    //ordered list
    void HandlerRead();
    void AddTimerInLoop(std::unique_ptr<TimerNode> timernode_uptr);
    void CancelTimeInLoop(TimerId timerid);

    std::vector<HashEntry> GetExpirationList(int64_t now_);
    bool Insert(std::unique_ptr<TimerNode> timernode_uptr);
    void Reset(const std::vector<HashEntry> & entrylist,int64_t now_);
    
    const int timerid;
    Event timeridevent;
    std::vector<HashEntry> ActiveList;
    std::vector<HashEntry> CancelList;

private:
    std::unordered_map<HashEntry,std::unique_ptr<TimerNode> > LookUp;
    orderd_timerlist header;//#0 timer 
};

