#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <queue>
#include <thread>
#include <map>
#include <functional>
#include <boost/core/noncopyable.hpp>  // boost::noncopyable
#include <memory>
#include "waitable_queue.hpp"
#include "priority_queue.hpp"
#include <iostream>
#include <functional>






namespace ilrd
{

class ThreadPool : private boost::noncopyable 
{
public:
    class ITask;
    enum priority_t
    {
        LOW = 0,
        MED,
        HIGH
    };

    explicit ThreadPool(size_t numOfThreads,unsigned int niceness);
    ~ThreadPool();

    void AddTask(std::shared_ptr<ITask> task, priority_t priority = MED)
    {
        m_TaskQueue.Push(task);
    }
    void Pause()
    {
        m_pause = true;/* plus join semi-destructor */
    }
    void Resume()
    {
        /* semi-constructor just for the map */
    }
    void SetNumOfThreads(size_t numOfThrads);

    class ITask : public boost::noncopyable
    {
    public:
        virtual void Run()=0;
        virtual ~ITask()
        {

        }
        virtual bool operator<(ITask &other)
        {
            return (priority < other.priority);
        }
        void SetPriority(priority_t set_to)
        {
            priority = set_to;
        }
    private:
        priority_t priority;
    };

    
    class FunctionTask : public ITask
    {
    public:
        explicit FunctionTask(std::function<void(void)> ptr, priority_t pr = LOW): m_func(ptr)
        {
            this->SetPriority(pr);
        }
        void Run()
        {
            m_func();
        }
    private:
        std::function<void(void)> m_func;
    };

    template<typename RETURN_TYPE>
    class FunctorTask : public ITask
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
        static void RunThread(ilrd::ThreadPool *TP);
        std::thread::id GetId() const;
        std::thread *m_thread;
    private:
    };

    bool m_pause;
    size_t m_numOfThreads;
    WaitableQueue <std::shared_ptr<ITask> , ilrd::PriorityQueue<std::shared_ptr<ITask>>> m_TaskQueue;
    std::map<std::thread::id ,WorkerThread*> m_ThreadMap;
    friend WorkerThread;
};



}//namespace ilrd

#endif /* __THREAD_POOL_HPP__ */