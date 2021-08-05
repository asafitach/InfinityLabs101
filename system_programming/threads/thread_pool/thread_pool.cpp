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
#include <semaphore.h>
#include <unistd.h>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>
#include <boost/interprocess/creation_tags.hpp>


/* ############################## Thread pool imp.  ############################## */

/* CTOR */
ilrd::ThreadPool::ThreadPool(size_t numOfThreads, unsigned int niceness):m_numOfThreads(numOfThreads), m_TaskQueue(), m_ThreadMap(), m_ThreadMapToDelete() 
{
    OpenThreds(m_numOfThreads);
}

void ilrd::ThreadPool::OpenThreds(size_t num_of_thread_to_open)
{
    WorkerThread *tmp = NULL;
    for (size_t i = 0; i < num_of_thread_to_open; i++)
    {
        tmp = new WorkerThread(this);
        m_ThreadMap[tmp->GetId()] = tmp;
        std::cout<<"threadpool ctor\t\t"<<tmp->GetId()<<std::endl;
    }
}


/* DTOR */
ilrd::ThreadPool::~ThreadPool() noexcept
{
    CloseThreds(m_numOfThreads);
}
 
void ilrd::ThreadPool::CloseThreds(size_t num_of_thread_to_close)
{
    boost::interprocess::named_semaphore dtor_sem(boost::interprocess::open_or_create, "dtor_semaphore", 0);
    ilrd::ThreadPool::FunctorTask<void> *obj = new ilrd::ThreadPool::FunctorTask<void>(ilrd::ThreadPool::badApple(this));
    std::shared_ptr<ilrd::ThreadPool::ATask> ptr2(obj);
    for (size_t i = 0; i < num_of_thread_to_close; i++)
    {
        AddTask(ptr2, ilrd::ThreadPool::priority_t::HIGH);
    }
    
    for (size_t i = 0; i < m_numOfThreads; i++)
    {
        dtor_sem.wait();
    }
    
    dtor_sem.remove("dtor_semaphore");

    std::map<std::thread::id ,WorkerThread*>::iterator iter = m_ThreadMap.begin();

    int counter = 0;
    while (iter != m_ThreadMap.end())
    {
        ++counter;

        // iter->second->m_thread->join();
        std::cout<<"DTOR "<<counter<</* "  id: "<<(iter->first)<< */std::endl;
        delete iter->second;
        ++iter;
    }
}

/* Add Task */
void ilrd::ThreadPool::AddTask(std::shared_ptr<ilrd::ThreadPool::ATask> task, ilrd::ThreadPool::priority_t priority)
{
    m_TaskQueue.Push(task);
}

/* Pause */
void ilrd::ThreadPool::Pause()
{
    boost::interprocess::named_semaphore pause_sem(boost::interprocess::open_or_create, "pause_sem_threadpool", 0);
    boost::interprocess::named_semaphore run_sem(boost::interprocess::open_or_create, "run_sem_threadpool", 0);
    
    ilrd::ThreadPool::FunctorTask<void> *obj = new ilrd::ThreadPool::FunctorTask<void>(ilrd::ThreadPool::threadToSleep());
    std::shared_ptr<ilrd::ThreadPool::ATask> ptr2(obj);
    for (size_t i = 0; i < m_numOfThreads; i++)
    {
        AddTask(ptr2, ilrd::ThreadPool::priority_t::HIGH);
    }
    for (size_t i = 0; i < m_numOfThreads; i++)
    {
        pause_sem.wait();
    }

    delete obj;
}

/* Resume */
void ilrd::ThreadPool::Resume()
{
    boost::interprocess::named_semaphore run_sem(boost::interprocess::open_or_create, "run_sem_threadpool", 0);
    for (size_t i = 0; i < m_numOfThreads; i++)
    {
        run_sem.post();
    }
}

/* Set Num Of Thread */
void ilrd::ThreadPool::SetNumOfThreads(size_t numOfThrads)
{
    if (numOfThrads >= m_numOfThreads)
    {
        OpenThreds(numOfThrads - m_numOfThreads);
    }
    else
    {
        CloseThreds(m_numOfThreads - numOfThrads);
    }
}


/* ############################## Worker Thread imp.  ############################## */

/* CTOR */
ilrd::ThreadPool::WorkerThread::WorkerThread(ilrd::ThreadPool *TP)
                        :m_stop(false), m_thread(new std::thread(ilrd::ThreadPool::RunThread, TP, this))
{
}

/* DTOR */
ilrd::ThreadPool::WorkerThread::~WorkerThread()
{
    if (!(m_thread->joinable()))
    m_thread->join();
    delete (m_thread);
    m_thread = NULL;
}

/* Run Thread */
void ilrd::ThreadPool::RunThread(ilrd::ThreadPool *TP, ilrd::ThreadPool::WorkerThread *worker)
{
    std::shared_ptr<ilrd::ThreadPool::ATask> fun_ptr;

    while (worker->m_stop)
    {
        TP->m_TaskQueue.Pop(fun_ptr);
        fun_ptr->Run();
        std::cout<<"thread id: "<<std::this_thread::get_id()<<" pause flag is: "<<worker->m_stop<<std::endl;
    }

}

/* Get Function */
std::thread::id ilrd::ThreadPool::WorkerThread::GetId()const
{
    return m_thread->get_id();
}

/* ##############################  ITask imp. ############################## */

ilrd::ThreadPool::ATask::~ATask()
{
}

bool ilrd::ThreadPool::ATask::operator<(ilrd::ThreadPool::ATask &other)
{
    return (priority < other.priority);
}

void ilrd::ThreadPool::ATask::SetPriority(ilrd::ThreadPool::priority_t set_to)
{
    priority = set_to;
}

/* ##############################  Function Task imp. ############################## */

/* CTOR */
ilrd::ThreadPool::FunctionTask::FunctionTask(std::function<void(void)> ptr, priority_t pr): m_func(ptr)
{
    this->SetPriority(pr);
}

/* Run */
void ilrd::ThreadPool::FunctionTask::Run()
{
    m_func();
}


/* ##############################   ############################## */
void ilrd::ThreadPool::threadToSleep::operator()()
{
    boost::interprocess::named_semaphore pause_sem(boost::interprocess::open_only, "pause_sem_threadpool");
    boost::interprocess::named_semaphore run_sem(boost::interprocess::open_only, "run_sem_threadpool");
    pause_sem.post();
    run_sem.wait();
}


ilrd::ThreadPool::badApple::badApple(ilrd::ThreadPool *TP):m_TP(TP)
{}

void ilrd::ThreadPool::badApple::operator()()
{
    boost::interprocess::named_semaphore dtor_sem(boost::interprocess::open_only, "dtor_semaphore");
    ThreadPool::WorkerThread *thread_to_stop = NULL;
    std::thread::id th_id = std::this_thread::get_id();
    thread_to_stop = m_TP->m_ThreadMap[th_id];
    thread_to_stop->m_stop = true;
    m_TP->m_ThreadMapToDelete[th_id] = thread_to_stop;
    dtor_sem.post();
}






class functor_task_2
{
private:
    static int x;
public:
    bool operator()()
    {
        ++x;
        std::cout<<"hello from task 2  ("<<x<<") \n";
        return true;
    }
};

int functor_task_2::x = 0;

void TaskOne();

int main()
{
    ilrd::ThreadPool pool(3,20);

    std::shared_ptr<ilrd::ThreadPool::FunctionTask> ptr(new ilrd::ThreadPool::FunctionTask(TaskOne, ilrd::ThreadPool::HIGH));
    ilrd::ThreadPool::FunctorTask<bool> *obj = new ilrd::ThreadPool::FunctorTask<bool>(functor_task_2());
    std::shared_ptr<ilrd::ThreadPool::ATask> ptr2(obj);


    pool.AddTask(ptr);
    pool.AddTask(ptr);
    pool.AddTask(ptr2);
    pool.Pause();
    std::cout<<"after pause\n";
    sleep(1);
    std::cout<<"noe resume\n";
    pool.Resume();
    pool.AddTask(ptr2);
    pool.AddTask(ptr);
    pool.AddTask(ptr2);
    pool.AddTask(ptr);
    pool.AddTask(ptr);
    pool.AddTask(ptr2);
    sleep(5);

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
