
#include "thread_pool.hpp"
#include <iostream>

namespace ilrd
{
using std::cout;
using std::endl;


ThreadPool::ThreadPool(size_t numOfThreads, unsigned int niceness) : m_numOfThreads(numOfThreads), 
                        m_sem(new boost::interprocess::interprocess_semaphore(0)), 
                        m_cond_var()
{
    (void)niceness;
    OpenThreads(numOfThreads);
}

void ilrd::ThreadPool::OpenThreads(size_t num_of_threads)
{
    for (size_t i = 0; i < num_of_threads; ++i)
    {
        WorkerThread *wt = new WorkerThread(this);
        this->m_threadVector[wt->GetId()] = wt;
    }
}

ThreadPool::~ThreadPool() 
{
    std::cout << "Start Dtor" << std::endl;
    PauseAll();
    std::map<std::thread::id, ilrd::ThreadPool::WorkerThread *>::iterator iter;
    for (iter = m_threadVector.begin(); iter != m_threadVector.end(); ++iter)
    {
        iter->second->Join();
        delete iter->second;
    }
    std::cout << "End Dtor" << std::endl;
    delete this->m_sem;
}


void ThreadPool::AddTask(std::shared_ptr<ATask> task, priority_t priority /* = MED */)
{
    task->SetPriority(priority);
    this->m_taskQueue.Push(task);
}

void ilrd::ThreadPool::PauseAll()
{
    std::map<std::thread::id, ilrd::ThreadPool::WorkerThread *>::iterator iter;
    for (iter = m_threadVector.begin(); iter != m_threadVector.end(); ++iter)
    {
        iter->second->SetPause(true);
    }
}

ThreadPool::WorkerThread::WorkerThread(ThreadPool *tp) :    m_toPause(false)
                            , m_thread(new std::thread(ThreadPool::WorkerThread::RunThread, tp, this))
{
    std::cout << GetId() <<std::endl;
}

void ThreadPool::WorkerThread::RunThread(ThreadPool *tp, ThreadPool::WorkerThread *wt)
{
    std::shared_ptr<ATask> res;
    while (!wt->m_toPause)
    {
        if(tp->m_taskQueue.Pop(res, ThreadPool::TIMEOUT))
        {
            res->Run();
        }
    }
}

ThreadPool::WorkerThread::~WorkerThread()
{
    delete m_thread;
}
 
std::thread::id ThreadPool::WorkerThread::GetId() const
{
    return (m_thread->get_id());
}

void ThreadPool::WorkerThread::Join()
{
    m_thread->join();
}

void ThreadPool::WorkerThread::SetPause(bool toPause)
{
    m_toPause = toPause;
}

bool ThreadPool::WorkerThread::GetPause()
{
    return (m_toPause);
}

ThreadPool::FunctionTask::FunctionTask(std::function<void(void)> ptr) : m_ptr(ptr) { }


void ThreadPool::FunctionTask::Run()
{
    m_ptr();
}

ThreadPool::priority_t ThreadPool::ATask::GetPriority()
{
    return (m_priority);
}

void ThreadPool::ATask::SetPriority(ThreadPool::priority_t priority)
{
    m_priority = priority;
}

ThreadPool::SleepingPill::SleepingPill(ThreadPool *tp) : m_tp(tp) { }

void ThreadPool::SleepingPill::operator()()
{
    m_tp->m_sem->post();
    std::unique_lock<std::mutex> lock(m_tp->m_lock);
    m_tp->m_cond_var.wait(lock);
}

ThreadPool::BadApple::BadApple(ThreadPool *tp) : m_tp(tp) { }

void ThreadPool::BadApple::operator()()
{
    std::thread::id this_id = std::this_thread::get_id();
    m_tp->m_threadVector[this_id]->SetPause(true);/*  */
    m_tp->m_sem->post();
    cout << "Bad Apple" << endl;
}


void ThreadPool::Pause()
{   
    for(size_t i = 0; i < this->m_numOfThreads; i++)
    {
        cout <<"Sleeping Pill" << endl;
        ThreadPool::FunctionTask *sleepTask = new ThreadPool::FunctionTask(SleepingPill(this));
        std::shared_ptr<ThreadPool::ATask> task(sleepTask);
        this->m_taskQueue.Push(task);
    }

    for(size_t i = 0; i < this->m_numOfThreads; i++)
    {
        this->m_sem->wait();
    }
}

void ThreadPool::Resume()
{
    this->m_cond_var.notify_all();
}

void ThreadPool::SetNumOfThreads(size_t numOfThrads)
{
    if(numOfThrads > m_numOfThreads)
    {
        OpenThreads(numOfThrads - m_numOfThreads);
    }
    else if(numOfThrads < m_numOfThreads)
    {
        for(size_t i = numOfThrads; i < m_numOfThreads; i++)
        {
            ThreadPool::FunctionTask *badApple = new ThreadPool::FunctionTask(BadApple(this));
            std::shared_ptr<ThreadPool::ATask> task(badApple);
            this->m_taskQueue.Push(task);
        }

        for(size_t i = numOfThrads; i < this->m_numOfThreads; i++)
        {
            this->m_sem->wait();
        }

        std::map<std::thread::id, ilrd::ThreadPool::WorkerThread *>::iterator iter;
        for (iter = m_threadVector.begin(); iter != m_threadVector.end();)
        {
            if (iter->second->GetPause()) // if the thread need to be killed
            {
                std::thread::id threadID = iter->second->GetId();
                std::cout << "kill thread: " << threadID << std::endl;
                iter->second->Join();
                delete iter->second;
                ++iter;
                this->m_threadVector.erase(threadID);
            }
            else
            {
                iter++;
            }

        }

    }
    
    m_numOfThreads = numOfThrads;
}

bool operator<(std::shared_ptr<ThreadPool::ATask> task1, std::shared_ptr<ThreadPool::ATask> task2)
{
    return (task1->GetPriority() < task2->GetPriority());
}






}//namespace ilrd