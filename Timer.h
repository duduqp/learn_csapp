#pragma once
#include "ddserver/Uncopyable.h"
#include <sys/types.h>
#include <stdint.h>
#include <functional>
#include <sys/time.h>
#include <stdio.h>


constexpr int UsPerSecond=1000*1000;
static int64_t Now(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*UsPerSecond+tv.tv_usec;
}


static int64_t  Add_Time(double seconds){
    int64_t now=Now();
    int64_t delta=seconds*UsPerSecond;
    return delta+now;
}


class Timer:Uncopyable
{
public:
    Timer(const double interval_,int64_t when,std::function<void()> callback):
     interval(interval_),seq(counter++),expiration(when),CallBack(callback),repeated(interval_>0.0){}
    ~Timer() {}

    void Run(){
        CallBack();
    }


    void Restart(int64_t now){
        if(IsRepeatable())
        {
            expiration=now+interval;
        }else{
            expiration=0;//0 is invalid
        }
    }

    //property
    int64_t GetSeq() const{return seq;}
    int64_t GetExpiration() const{return expiration;}
    bool IsRepeatable() const{return repeated;}

private:
    static int64_t counter;
    const double interval;//interval time between two respond
    int64_t seq;
    int64_t expiration;
    std::function<void()> CallBack;
    const bool repeated;//is a repeat timer?
};

