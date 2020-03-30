#include "Timer.h"
#include <sys/time.h>
#include <unistd.h>
#include <memory>


TimeNode::TimeNode(std::shared_ptr<RequestContent> req,
                   int timeout_msecs):isdeleted(false),req_content(req){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    //calcu in msec
    expiredtime=(tv.tv_sec%10000)*1000+tv.tv_usec/1000+timeout_msecs;
}

TimeNode::~TimeNode()
{
    if(req_content) req_content->Handle_Close();
}


TimeNode::TimeNode(TimeNode & l):req_content(l.req_content),expiredtime(0){

}


void TimeNode::Update(int timeout_msecs)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    expiredtime=(tv.tv_sec%10000)*1000+tv.tv_usec/1000+timeout_msecs;
}

void TimeNode::ClearReq(){
    req_content.reset();//release shared_ptr
    SetDeleted();
}



bool TimeNode::Valid(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    size_t tmp=(tv.tv_sec%10000)*1000+tv.tv_usec/1000;
    if(tmp>expiredtime)
    {
        //expired
        SetDeleted();
    }
    return tmp<expiredtime;
}

void TimeNode::SetDeleted(){
    isdeleted=true;
}

//Timer

void Timer::AddTimeNode(std::shared_ptr<RequestContent> req,int timeout_secs)
{
    ptr_TimeNode new_node(new TimeNode(req,timeout_secs));
    event_timenodes.push(new_node);
    req->LinkTimer(new_node);
}

//call for lazy delete
void Timer::Handle_Expired(){
    //mutex ?
    while(!event_timenodes.empty())
    {
        //must use another sharedptr to judge
        ptr_TimeNode tmp=event_timenodes.top();
        if(tmp->Deleted())
        {
            event_timenodes.pop();
        }else if(!tmp->Valid())
        {
            event_timenodes.pop();
        }else{
            break;
        }

    }
}













