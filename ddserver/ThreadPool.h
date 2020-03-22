#pragma once
#include "Event.h"
#include <pthread.h>
#include <functional>
#include <deque>
#include <vector>
#include <memory>
#include "MutexLock_Util.h"
#include "SyncCondition.h"

typedef enum{
    IMMEDIATE = 1,
    GRACEFULLY
} ShutDownOpt;


const int TASK_ADD_SUCCESS=0;
const int TASK_ADD_ERROR=-1;

const int THREADPOOL_START_SUCCESS=0;
const int THREADPOOL_START_ERROR=-1;

const int THREADPOOL_STOP_SUCCESS=0;
const int THREADPOOL_STOP_ERROR=-1;
struct Task{
    std::function<void(std::shared_ptr<void>)> func;
    std::shared_ptr<void> args;
};

//bounded threadpool for compute-intense-task
class ThreadPool
{
public:
    explicit ThreadPool(int max_task_num_,int worker_num_=4):
    mutex(MutexLock()),NotFull(mutex),NotEmpty(mutex),running(false)
    ,shutdownopt(ShutDownOpt::GRACEFULLY){
        workers.reserve(worker_num);
    }
    ~ThreadPool() {
        if(shutdownopt==ShutDownOpt::IMMEDIATE)
        {

        }else{

        }
    }
    static void * ThreadPool_Routine(void *);
    int Start();//bind this ptr since non-static(member function mangling)    
    int Add(Task t);
    int Stop();
private:
     MutexLock mutex;
     SyncCondition NotFull;
     SyncCondition NotEmpty;
     std::vector<pthread_t> workers;
     std::deque<Task> tasks;
     int max_task_num;
     int worker_num;
     bool running;
     ShutDownOpt shutdownopt;
};

