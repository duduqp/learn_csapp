#include "Thread.h"
#include <sys/types.h>
#include <assert.h>
#include <sys/prctl.h>
#include "CurrentThread.h"
#include <iostream>
namespace CurrentThread{
 __thread int t_cached_tid=0;
void Cachetid();
}
pid_t gettid() { return static_cast<pid_t>(::syscall(SYS_gettid)); }
void CurrentThread::Cachetid()
{
    if(t_cached_tid==0)
    {
        t_cached_tid=gettid();
    }
}
struct ThreadData{
   typedef std::function<void()> ThreadFunc;
   ThreadFunc func_;
   pid_t * tid_;
   CountDownLatch * latch_;

   ThreadData(const ThreadFunc  & func,pid_t * tid,CountDownLatch* latch):
       func_(func),tid_(tid),latch_(latch){
           std::cout<<__FUNCTION__<<std::endl;
           std::cout <<&func_<<std::endl;
       }

   void RunInLocal()
   {
       std::cout<< "Thread Data RunInLocal"<<std::endl;
     *tid_=CurrentThread::tid();
     std::cout << "Thread Data RunInLocal :tid"<<*tid_<<std::endl;
     tid_=nullptr;
     latch_->DropOne();
     latch_=nullptr;
     func_();
   }


};

void * startthread(void * data)
{
    std::cout << "startthread hook" << std::endl;
    ThreadData * threaddata=static_cast<ThreadData *>(data);
    threaddata->RunInLocal();
    delete threaddata;
    return nullptr;
}

Thread::Thread(const ThreadFunc & func_):ThreadId(0), tid(0),started(false)
                                        ,joined(false),func(func_), latch(1)
{
    std::cout <<  "thread ctor"<<std::endl;
}


Thread::~Thread(){
    if(started&&!joined){
        pthread_detach(ThreadId);
    }
}

void Thread::Start(){
    assert(!started);
   
    started=true;
    std::cout << "Thread Start  tid:"<<tid<<std::endl;
    ThreadData * data=new ThreadData(func,&tid,&latch);
    if(pthread_create(&ThreadId,NULL,startthread,data))
    {
        //return errorno!=0
        std::cout << "Thread Start create fail"<<std::endl;
        started=false;
        delete data;
        return ;
    }else{
        std::cout << "Thread Start create ok"<<std::endl;
        std::cout << ThreadId<<std::endl;
        latch.Wait();
        std::cout << __FUNCTION__<<"tid:"<<tid << std::endl;
        std::cout <<__FUNCTION__ << "thread func?"<<&func<<std::endl;
        assert(tid>0);
    }
}

int Thread::Join(){
    assert(started&&!joined);
    joined=true;
    return pthread_join(ThreadId,NULL);
}




