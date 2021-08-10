#include <thread>  //std::thread
#include <utility> //std::pair
#include <queue>
#include <boost/asio/time_traits.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/system/error_code.hpp>
#include "scheduler.hpp"

/* ########## scheduler  ########## */

ilrd::Scheduler::Scheduler():m_isRunning(true), m_startToRun(new boost::interprocess::interprocess_semaphore(0)), m_pqueue(),  m_thread(RunningThread, this)
{
}

ilrd::Scheduler::~Scheduler()
{
    m_isRunning = false;
    m_thread.join();
}

void ilrd::Scheduler::AddTask(std::shared_ptr<ilrd::Scheduler::ITask> task, time_t delay)
{
    m_pqueue.push(std::pair<time_t, std::shared_ptr<ITask>>(delay, task));
}


void ilrd::Scheduler::Run()
{
    m_startToRun->post();
}


/*########## Itask  ########## */

ilrd::Scheduler::ITask::~ITask()
{
}

void ilrd::Scheduler::RunningThread(ilrd::Scheduler *sched)
{
    sched->m_startToRun->wait();
    while (true == sched->m_isRunning && false == sched->m_pqueue.empty())
    {
        std::pair<time_t, std::shared_ptr<ITask>> cur_task = sched->m_pqueue.top();
        sched->m_pqueue.pop();

        boost::asio::io_context io;
        // Construct a timer without setting an expiry time.
        boost::asio::deadline_timer timer(io);
        // Set an expiry time relative to now.
        timer.expires_from_now(boost::posix_time::seconds(cur_task.first));
        // Wait for the timer to expire.
        timer.wait();

        cur_task.second->Execute();
    }

}

int ilrd::operator<(ilrd::Scheduler::TimeAndTask &left, ilrd::Scheduler::TimeAndTask &right)
{
    return (left.first > right.first);
}