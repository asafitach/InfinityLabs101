#ifndef _ILRD_RD101_LOGGER_H
#define _ILRD_RD101_LOGGER_H

// #include <time>
#include <string>
#include <mutex>
#include <iostream>
#include <fstream>
#include "singleton.hpp"
#include "thread_pool.hpp"
#include "handleton.hpp"

namespace ilrd
{

class Logger
{
public:
    enum severity_t
    {
        WARNING = 0,
        INFO,
        ERROR
    };
    void Log(time_t time, severity_t severity, std::string str_to_write);
    virtual ~Logger();
    friend ilrd::Singleton<Logger>;
    friend ilrd::Handleton<ilrd::Logger>;

private:
    class loggerTask 
    {
    public:
        loggerTask(time_t time, severity_t severity, std::string str_to_write, Logger *log);
        bool operator()();
    
    private:
        time_t m_time;
        severity_t m_severity;
        std::string m_str_to_write;
        Logger *m_log;
    };

    ThreadPool *m_pool;
    std::ofstream m_log_streamer;
    std::mutex m_lock;
    std::shared_ptr<ThreadPool::FutureTask<bool>> m_task_ptr;

    Logger();
    friend loggerTask;
};


}//ilrd

#endif //_ILRD_RD101_LOGGER_H