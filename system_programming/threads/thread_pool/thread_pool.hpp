#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <queue>
#include <thread>
#include <map>
#include <functional>
#include <boost/core/noncopyable.hpp>  // boost::noncopyable
#include <memory>
#include "waitable_queue.hpp"
#include "pqueue_wrap.hpp"
#include <iostream>
#include <functional>



namespace ilrd
{

class ThreadPool : private boost::noncopyable 
{
private:
    class WorkerThread;
public:
    class ATask;
    enum priority_t
    {
        LOW = 0,
        MED,
        HIGH
    };

    explicit ThreadPool(size_t numOfThreads,unsigned int niceness);
    ~ThreadPool();

    void AddTask(std::shared_ptr<ATask> task, priority_t priority = MED);
    void Pause();
    void Resume();
    void SetNumOfThreads(size_t numOfThrads);
    static void RunThread(ilrd::ThreadPool *TP, ilrd::ThreadPool::WorkerThread *worker);

    class badApple
    {
    private:
        ThreadPool *m_TP;
    public:
        badApple(ThreadPool *TP);
        void operator()();

    };
    class threadToSleep
    {
    private:
    public:
        void operator()();
    };


    class ATask : public boost::noncopyable
    {
    public:
        virtual void Run()=0;
        virtual ~ATask();
        virtual bool operator<(ATask &other);
        void SetPriority(priority_t set_to);

    private:
        priority_t priority;
    };

    
    class FunctionTask : public ATask
    {
    public:
        explicit FunctionTask(std::function<void(void)> ptr, priority_t pr = LOW);
        void Run();
    private:
        std::function<void(void)> m_func;
    };

    template<typename RETURN_TYPE>
    class FunctorTask : public ATask
    {
    public:
        explicit FunctorTask(std::function<RETURN_TYPE(void)> functor, priority_t pr = LOW): m_functor(functor)
        {
            this->SetPriority(pr);
        }
        void Run()
        {

            m_functor();
        }
        RETURN_TYPE Get()
        {

            return m_functor();
        }
    private:
        std::function<RETURN_TYPE(void)> m_functor;
    };

private:
    class WorkerThread
    {
    public: 
        WorkerThread(ThreadPool *TP);
        ~WorkerThread();
        std::thread::id GetId() const;
        void join()
        {
            if (!(m_thread->joinable()))
            m_thread->join();
        }
        bool m_stop;
        std::thread *m_thread;
    private:
    };


    size_t m_numOfThreads;
    void CloseThreds(size_t num_of_thread_to_close);
    void OpenThreds(size_t num_of_thread_to_open);
    WaitableQueue <std::shared_ptr<ATask> , ilrd::PriorityQueue<std::shared_ptr<ITask>>> m_TaskQueue;
    std::map<std::thread::id ,WorkerThread*> m_ThreadMap;
    std::map<std::thread::id ,WorkerThread*> m_ThreadMapToDelete;
};



}//namespace ilrd

#endif /* __THREAD_POOL_HPP__ */