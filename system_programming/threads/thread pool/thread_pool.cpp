#include <queue>
#include <thread>
#include <map>
#include <iterator>
#include <functional>
#include <boost/core/noncopyable.hpp>  // boost::noncopyable
#include <memory>
#include "waitable_queue.hpp"
#include "priority_queue.hpp"
#include "thread_pool.hpp"
#include <iostream>
#include <unistd.h>


ilrd::ThreadPool::ThreadPool(size_t numOfThreads, unsigned int niceness):m_pause(false), m_numOfThreads(numOfThreads), m_TaskQueue(), m_ThreadMap() 
{
    WorkerThread *tmp = NULL;
    for (size_t i = 0; i < numOfThreads; i++)
    {
        tmp = new WorkerThread(this);
        m_ThreadMap[tmp->GetId()] = tmp;
        std::cout<<"threadpool ctor"<<tmp->GetId()<<std::endl;
    }
}

ilrd::ThreadPool::~ThreadPool() noexcept
{
    std::map<std::thread::id ,WorkerThread*>::iterator iter = m_ThreadMap.begin();
    m_pause = true;
    while (iter != m_ThreadMap.end())
    {
        iter->second->m_thread->join();
        ++iter;
    }
}

void ilrd::ThreadPool::WorkerThread::RunThread(ilrd::ThreadPool *TP)
{
    std::shared_ptr<ilrd::ThreadPool::ITask> fun_ptr;
    
    while (!TP->m_pause)
    {
        TP->m_TaskQueue.Pop(fun_ptr);
        fun_ptr->Run();
    }
    std::thread::id this_id = std::this_thread::get_id();
    std::cout<<"this is the run func"<<this_id<<std::endl;

}

ilrd::ThreadPool::WorkerThread::WorkerThread(ilrd::ThreadPool *TP)
                        : m_thread(new std::thread(ilrd::ThreadPool::WorkerThread::RunThread, TP))
{
}

ilrd::ThreadPool::WorkerThread::~WorkerThread()
{}

std::thread::id ilrd::ThreadPool::WorkerThread::GetId()const
{
    return m_thread->get_id();
}

/* void ilrd::ThreadPool::ITask::Run()
{

}
 */


class functor_task_2
{
private:
    /* data */
public:
    bool operator()()
    {
        std::cout<<"hello from task 2\n";
        return true;
    }
};



void TaskOne();

int main()
{
    ilrd::ThreadPool pool(1,20);
    std::function<void(void)> fun(TaskOne);
    std::function<bool(void)> fun2(functor_task_2());
    std::shared_ptr<ilrd::ThreadPool::FunctionTask> ptr(new ilrd::ThreadPool::FunctionTask(TaskOne, ilrd::ThreadPool::HIGH));

    // std::shared_ptr<ilrd::ThreadPool::FunctorTask> ptr(new ilrd::ThreadPool::FunctorTask<bool(void)>(fun2));
    ilrd::WaitableQueue<int, ilrd::PriorityQueue<int>> Q_k;
    fun();

    Q_k.Push(78);
    Q_k.Push(9);
    Q_k.Push(8);
    int ppi;
    Q_k.Pop(ppi);
    std::cout<<" "<<ppi<<" ";
    
    Q_k.Pop(ppi);
    std::cout<<" "<<ppi<<" ";
    
    Q_k.Pop(ppi);
    std::cout<<" "<<ppi<<" ";
    

    fun2();

/* 
    std::shared_ptr<ilrd::ThreadPool::ITask> ptr = new ilrd::ThreadPool::FunctorTask<void ()>(fun); */
    pool.AddTask(ptr);
    sleep(2);

    pool.Pause();
    return 0;
}

void TaskOne()
{
    std::cout<<"hello from task one\n";
}


/* 
bool Task2()
{
// } */
// template<class RETURN_TYPE> 
// ilrd::ThreadPool::FunctorTask<RETURN_TYPE>::FunctorTask(std::function<RETURN_TYPE ()> functor)
