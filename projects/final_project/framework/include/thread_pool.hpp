#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <queue>
#include <thread>
#include <map>
#include <functional>
#include <atomic>
#include <boost/core/noncopyable.hpp>  // boost::noncopyable
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <future>

#include "waitable_queue.hpp"
#include "pqueue_wrap.hpp"

namespace ilrd
{

class ThreadPool : private boost::noncopyable 
{
public:
    class ATask;
    enum priority_t
    {
        LOW = 0,
        MED,
        HIGH
    };
    static const int TIMEOUT = 500;
    explicit ThreadPool(size_t numOfThreads, unsigned int niceness);
    virtual ~ThreadPool();
    void AddTask(std::shared_ptr<ATask> task, priority_t priority = MED);
    void Pause();
    void Resume();
    void SetNumOfThreads(size_t numOfThrads);
    

    class ATask : public boost::noncopyable  
    {
    public:
        virtual void Run()=0;
        virtual ~ATask() {}
        priority_t GetPriority();
        void SetPriority(priority_t priority);
    private:
        priority_t m_priority;
    };

    
    class FunctionTask : public ATask
    {
    public:
        explicit FunctionTask(std::function<void(void)> ptr);
        void Run();
    private:
        std::function<void(void)> m_ptr;
    };

    template<typename RETURN_TYPE>
    class FutureTask : public ATask
    {
    public:
        explicit FutureTask(std::function<RETURN_TYPE(void)> functor);
        void Run();
        RETURN_TYPE Get();
    private:
        std::function<RETURN_TYPE(void)> m_functor;
        std::promise<RETURN_TYPE> m_promiseObj;
    };

private:
    class WorkerThread
    {
    public:
        WorkerThread(ThreadPool *tp);
        ~WorkerThread();
        std::thread::id GetId() const;
        void Join();
        void SetPause(bool toPause);
        bool GetPause();
        

    private:
        std::atomic<bool> m_toPause;
        std::thread *m_thread;
        static void RunThread(ThreadPool *tp, WorkerThread *wt);
    };

    class SleepingPill
    {
    public:
        SleepingPill(ThreadPool *tp);
        void operator()(void);
    private:
        ThreadPool *m_tp;
    };

    class BadApple
    {
    public:
        BadApple(ThreadPool *tp);
        void operator()(void);
    private:
        ThreadPool *m_tp;
    };

    WaitableQueue <std::shared_ptr<ATask>, PriorityQueue<std::shared_ptr<ATask>>> m_taskQueue;
    size_t m_numOfThreads;
    std::map<std::thread::id ,WorkerThread *> m_threadVector;
    std::atomic<bool> m_keepRunning;
    boost::interprocess::interprocess_semaphore *m_sem;
    std::condition_variable m_cond_var;
    std::mutex m_lock;
    

    void PauseAll();
    void OpenThreads(size_t num_of_threads);
};

template<typename RETURN_TYPE>
ThreadPool::FutureTask<RETURN_TYPE>::FutureTask(std::function<RETURN_TYPE(void)> functor) : m_functor(functor) { } 
                                                                    

template<typename RETURN_TYPE>
void ThreadPool::FutureTask<RETURN_TYPE>::Run()
{
    this->m_promiseObj.set_value(this->m_functor());   
}

template<typename RETURN_TYPE>
RETURN_TYPE ThreadPool::FutureTask<RETURN_TYPE>::Get()
{
    std::future<RETURN_TYPE> futureObj;
    futureObj = this->m_promiseObj.get_future();
    return futureObj.get();  
}


}//namespace ilrd

#endif /* __THREAD_POOL_HPP__ */