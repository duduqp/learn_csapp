#pragma once
#include "MutexLock_Util.h"
#include "SyncCondition.h"
#include <list>
#include <stdlib.h>


template<typename T>
class blocking_queue
{
public:
    blocking_queue(int expect_max_size=1000):
        queue_mutex(),queue_cond(queue_mutex),max_queue_size(expect_max_size) {
        if(max_queue_size<0) max_queue_size=1000;
     }
    
    bool isfull() const;
    bool isempty() const;

    int size() const;
    int capacity() const;

    bool front(T & t);
    bool back(T & t);

    bool enqueue(const T &);
    bool pop(T & t) ;//stl style
    bool popuntil(T & t,int secs=20);//20s



    ~blocking_queue() {
        //nothing to do , list is stl-controled mutex and condition are RAII
    }

private:
    MutexLock queue_mutex;
    SyncCondition queue_cond;
    int max_queue_size;
    std::list<T> queue_; 
};

