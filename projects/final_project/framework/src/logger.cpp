#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "logger.hpp"

/* ###################  Logger ################### */

ilrd::Logger::Logger(): m_pool(new ilrd::ThreadPool (1, 20)),  m_lock(), m_task_ptr(NULL)
{
    m_log_streamer.open("./LOG.txt", std::ios::app);
}

void ilrd::Logger::Log(time_t time, ilrd::Logger::severity_t severity, std::string str_to_write)
{
    std::shared_ptr<ThreadPool::FutureTask<bool>> task_ptr = std::make_shared<ThreadPool::FutureTask<bool>>(ilrd::Logger::loggerTask(time, severity, str_to_write, this));
    std::unique_lock<std::mutex> till_scope_die(m_lock);
    m_task_ptr = task_ptr;
    m_pool->AddTask(task_ptr);
}

ilrd::Logger::~Logger()
{
    if (NULL != m_task_ptr)
    m_task_ptr->Get();
    delete m_pool;
    m_log_streamer.close();
}

/* ###################  Logger Task ################### */

ilrd::Logger::loggerTask::loggerTask(time_t time, ilrd::Logger::severity_t severity, std::string str_to_write, ilrd::Logger *log): m_time(time), m_severity(severity), m_str_to_write(str_to_write), m_log(log)
{
}

bool ilrd::Logger::loggerTask::operator()()
{
    std::string str;
    switch (m_severity)
    {
    case WARNING:
        str = "Warning";
        break;

    case ERROR:
        str = "Error";
        break;
    case INFO:
        str = "Info";
        break;
    }
    m_log->m_log_streamer<<m_time<<" "<<m_str_to_write<<" "<<str<<std::endl;
    return true;
}

