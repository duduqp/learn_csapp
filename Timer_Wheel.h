#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <unordered_set>
#include <queue>
#include <deque>
#include "TcpConnection.h"

struct Entry{
    explicit Entry(const std::weak_ptr<TcpConnection> & weakconn_):
        weakconn(weakconn_){}
    ~Entry(){
        std::shared_ptr<TcpConnection> sharedconn=weakconn.lock();
        if(sharedconn)
        {
            sharedconn->shutdown();
        }
    }
    
    std::weak_ptr<TcpConnection> weakconn;
};

struct EntryHash{
public:
    size_t operator()(const std::shared_ptr<Entry> & e)
    {
        return std::hash<std::shared_ptr<Entry>>()(e);
    }
};

class Timer_Wheel
{
public:
    Timer_Wheel() {}
    ~Timer_Wheel() {}

private:
    typedef std::shared_ptr<Entry> EntryPtr;
    typedef std::weak_ptr<Entry> WeakEntryPtr;
    typedef std::unordered_set<EntryPtr> Bucket;
    typedef std::deque<Bucket> WeakConnList; 
};

