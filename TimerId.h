#pragma once
#include "Timer.h"
#include "Timer_Queue.h"


class TimerId
{
public:
    TimerId():seq(0),timer(NULL) {}
    TimerId(int64_t seq_,Timer * timer_):seq(seq_),timer(timer_) {}

    friend  class Timer_Queue;
private:
    int64_t seq;
    Timer * timer;
};

