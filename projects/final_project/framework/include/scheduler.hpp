#ifndef __SCHEDULER_HPP__
#define __SCHEDULER_HPP__

#include <thread>  //std::thread
#include <utility> //std::pair
#include <queue>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include "handleton.hpp"

namespace ilrd
{


class Scheduler
{
public:
    class ITask;

    friend Handleton<Scheduler>;
    typedef std::pair<time_t, std::shared_ptr<ITask>> TimeAndTask;

    // delay is in second units
    void AddTask(std::shared_ptr<ITask> task, time_t delay);

    //after calling this method, you can't use add task
    void Run(); 

    class ITask
    {
    public:
        virtual void Execute(void) = 0;
        virtual ~ITask();
    };
        

private:
    Scheduler();
    ~Scheduler();
    static void RunningThread(Scheduler *sched);

    bool m_isRunning;
    boost::interprocess::interprocess_semaphore *m_startToRun;
    std::priority_queue<TimeAndTask> m_pqueue;
    std::thread m_thread;
};

int operator<(Scheduler::TimeAndTask &left, Scheduler::TimeAndTask &right);


}//namespace ilrd

#endif /* __SCHEDULER_HPP__ */