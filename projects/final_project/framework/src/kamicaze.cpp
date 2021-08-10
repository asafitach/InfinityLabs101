#include <sha
#include "handleton.hpp"
#include "scheduler.hpp"
#include "kamicaze.hpp"

ilrd::Kamikaze::Kamikaze(std::function<bool ()> action, time_t delay): m_action(action), m_delaySec(delay)
{
    AddTAsk();
}


void ilrd::Kamikaze::AddTAsk()
{
    ilrd::Scheduler *hendelton_sched = ilrd::Handleton<ilrd::Scheduler>::GetInstance();
    std::shared_ptr<Scheduler::ITask>taskPtr(new ilrd::Kamikaze::KamikazeTask(*this));

    hendelton_sched->AddTask(taskPtr, m_delaySec);
}

void ilrd::Kamikaze::KamikazeTask::Execute()
{
    m_Kamikaze.PerformAction();
}

void ilrd::Kamikaze::PerformAction()
{
    if (true == m_action())
    {
        AddTAsk();
    }
    else
    {
        delete this;
    }
}


ilrd::Kamikaze::KamikazeTask::KamikazeTask(ilrd::Kamikaze &kamikaze): m_Kamikaze(kamikaze)
{
}