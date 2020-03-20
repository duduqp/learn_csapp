#include "blocking_queue.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



template<typename T>
bool blocking_queue<T>::isfull() const{
    return queue_.size()==max_queue_size;
}

template<typename T>
bool blocking_queue<T>::isempty() const{
    return queue_.empty();
}

template<typename T>
int blocking_queue<T>::size() const
{
    int tmp;
    queue_mutex.Lock();
    tmp=queue_.size();
    queue_mutex.Unlock();
    return tmp;
}

template<typename T>
int blocking_queue<T>::capacity() const{
    return max_queue_size;
}

template<typename T>
bool blocking_queue<T>::enqueue(const T & t)
{
    queue_mutex.Lock();
    if(queue_.size()>=max_queue_size)
    {
        //full
        queue_cond.NotifyAll();
        //quit
        queue_mutex.Unlock();
        return false;
    }
    queue_.push_back(t);
    queue_cond.NotifyAll();
    queue_mutex.Unlock();
    return true;
}

template<typename T>
bool blocking_queue<T>::pop(T & t)
{
    queue_mutex.Lock();
    while(queue_.size()<=0)
    {
        if(0!=queue_cond.Wait())
        {
            //error occur and can not release mutex
            queue_mutex.Unlock();
            return false;
        }
    }
    //out queue
    t=queue_.front();
    queue_.pop_front();
    queue_mutex.Unlock();
    return true;

}

template<typename T>
bool blocking_queue<T>::popuntil(T & t,int secs)
{
    queue_mutex.Lock();
    while(queue_.empty())
    {
        if(0!=queue_cond.WaitUntil(secs))
        {
            queue_mutex.Unlock();
            return false;
        }
    }
    t=queue_.front();
    queue_.pop_front();
    queue_mutex.Unlock();
    return true;

}







template<typename T>
bool  blocking_queue<T>::back(T & t)
{
    queue_mutex.Lock();
    if(queue_.empty()==0)
    {
        queue_mutex.Unlock();
        return false;
    }
    t=queue_.back();
    queue_mutex.Unlock();
    return true;
}

template<typename T>
bool blocking_queue<T>::front(T & t)
{
    queue_mutex.Lock();
    if(queue_.empty())
    {
        queue_mutex.Unlock();
        return false;
    }
    t=queue_.front();
    queue_mutex.Unlock();
    return true;
}



