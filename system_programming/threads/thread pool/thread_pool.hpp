#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <queue>
#include <thread>
#include <map>
#include <functional>
#include <boost/core/noncopyable.hpp>  // boost::noncopyable
#include "waitable_queue.hpp"
#include "priority_queue_wrap.hpp"

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
    void AddTask(std::shared_ptr<Task> task, priority_t priority = MED);
    void Pause();
    void Resume();
    void SetNumOfThreads(size_t numOfThrads);

    class ITask : public boost::noncopyable
    {
    public:
        virtual void Run()=0;
        virtual ~ITask();
    private:
    };

    
    class FunctionTask : public ITask
    {
    public:
        explicit FunctionTask(std::function<void(void)> ptr);
        void Run();
    private:
        std::function<void(void)> ptr;
    };

    template<typename RETURN_TYPE>
    class FunctorTask : public ITask
    {
    public:
        explicit FunctorTask(std::function<RETURN_TYPE(void)> functor);
        void Run();
        RETURN_TYPE Get();
    private:
        std::function<RETURN_TYPE(void)> functor;
    };

private:
    class WorkerThread
    {
    public:
        WorkerThread();
        ~WorkerThread();
        std::thread::id GetId() const;
    private:
        std::thread m_thread;
    };
    WaitableQueue <std::shared_ptr<ITask> , Pqueue<std::shared_ptr<ITask>>> m_TaskQueue;
    size_t m_numOfThreads;
    std::map<std::thread::id ,WorkerThread> m_ThreadVector;
};

}//namespace ilrd

#endif /* __THREAD_POOL_HPP__ */