#ifndef __KAMIKAZE_HPP__
#define __KAMIKAZE_HPP__

# include "scheduler.hpp"

namespace ilrd
{

//instantiate only by using new

class Kamikaze 
{
public:
    explicit Kamikaze(std::function<bool()> action, time_t delay); 


    friend class KamikazeTask; 

private:
    
    class KamikazeTask : public Scheduler::ITask
    {
    public:
        KamikazeTask(Kamikaze &kamikaze);
        void Execute(); 
    private:
        Kamikaze& m_Kamikaze; 
    };
    void AddTAsk();
    void PerformAction(); 
    std::function<bool()> m_action; //returns repeat or not
    time_t m_delaySec; 
}; 


}//namespace ilrd

#endif /* __KAMIKAZE_HPP__ */