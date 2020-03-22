#pragma once
#include <time.h>
#include  "MutexLock_Util.h"
#include "SyncCondition.h"
#include "RequestContent.h"

#include <iostream>
#include <queue>

class RequestContent;


class TimeNode{
public:
    TimeNode(std::shared_ptr<RequestContent> req,int timeout_msecs);
    ~TimeNode();
    TimeNode(TimeNode & );
    void Update(int timeout_msecs);
    void ClearReq();//for reuse
    void SetDeleted();

    bool Valid() const;
    bool Valid() ;
    bool Deleted() const{ return isdeleted; }

    size_t GetExpired() const { return expiredtime; }

private:
    bool isvalid;
    bool isdeleted;

    size_t expiredtime;

    std::shared_ptr<RequestContent> req_content;

};



class Timer
{
    typedef std::shared_ptr<TimeNode> ptr_TimeNode;
public:
    Timer() {}
    ~Timer() {}
    void AddTimeNode(std::shared_ptr<RequestContent> req_content,int timeout_secs);
    void Handle_Expired();

private:
    struct TimeNodeCmp{
        bool operator()(const ptr_TimeNode & l,const ptr_TimeNode & r) const{
            return l->GetExpired()>r->GetExpired();//min-heap
        }
    };
    std::priority_queue<ptr_TimeNode,std::deque<ptr_TimeNode>,TimeNodeCmp> event_timenodes;
    MutexLock mutex;

};

