#include "Thread.h"
#include <sys/types.h>
#include <assert.h>
#include <sys/prctl.h>
#include "CurrentThread.h"
namespace CurrentThread{
 __thread int t_cached_tid;
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

   ThreadData(const ThreadFunc & func,pid_t * tid,CountDownLatch* latch):
    func_(func),tid_(tid),latch_(latch){}

   void RunInLocal()
   {
     *tid_=CurrentThread::tid();
     tid_=nullptr;
     func_();
   }


};

void * startthread(void * data)
{
    ThreadData * threaddata=static_cast<ThreadData *>(data);
    threaddata->RunInLocal();
    delete threaddata;
    return nullptr;
}

Thread::Thread(const ThreadFunc & func_):ThreadId(0), tid(0),started(false)
                                        ,joined(false),func(func_), latch(1)
{

}


Thread::~Thread(){
    if(started&&!joined){
        pthread_detach(ThreadId);
    }
}

void Thread::Start(){
    assert(!started);
    started=true;
    ThreadData * data=new ThreadData(func,&tid,&latch);
    if(pthread_create(&ThreadId,NULL,startthread,data))
    {
        //return errorno!=0
        started=false;
        delete data;
        return ;
    }
    latch.Wait();
    assert(tid>0);
}

int Thread::Join(){
    assert(started&&!joined);
    joined=true;
    return pthread_join(ThreadId,NULL);
}




