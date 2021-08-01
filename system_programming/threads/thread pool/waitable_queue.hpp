#ifndef __WAITABLE_QUEUE_HPP__
#define __WAITABLE_QUEUE_HPP__

#include <mutex>          // std::mutex
#include <condition_variable> // std::cond
#include <boost/core/noncopyable.hpp>  // boost::noncopyable
#include <iostream>

namespace ilrd
{

template <typename T, class queueType>
class WaitableQueue : private boost::noncopyable
{
public:
    bool Pop(T &outParam, time_t timeOut);
    void Pop(T &outParam); 
    void Push(const T &data);
    size_t Size() const; // add comment to user
    bool IsEmpty() const;

private:
    queueType m_queue;
    mutable std::mutex m_mutex; // will be passed to the scope lock
    std::condition_variable m_cond; 
};


template<typename T, typename queueType>
bool ilrd::WaitableQueue<T, queueType>::Pop(T &outParam, time_t timeOut)
{
    std::unique_lock<std::mutex> lock(this->m_mutex);
    std::cv_status status = std::cv_status::no_timeout;

    if (this->m_queue.empty())
    {
        while (this->m_queue.empty() && status == std::cv_status::no_timeout)
        {
            status = this->m_cond.wait_for(lock, std::chrono::milliseconds(timeOut));
        }
    }
    
    if (!this->m_queue.empty())
    {
        outParam =  this->m_queue.front();
        this->m_queue.pop();
        return (true);
    }

    return (false);
}



template <typename T, class queueType>
void WaitableQueue<T, queueType>::Pop(T &outParam)
{
    std::cerr << "Waiting... \n";

    std::unique_lock<std::mutex> lock(this->m_mutex);
    while (this->m_queue.empty())
    {
        this->m_cond.wait(lock);
    }

    std::cerr << "...finished waiting\n";
    outParam = this->m_queue.front();
    this->m_queue.pop();
}


template <typename T, class queueType>
void WaitableQueue<T, queueType>::Push(const T &data)
{
    std::unique_lock<std::mutex> lock(this->m_mutex);
    m_queue.push(data);
    m_cond.notify_one(); 
}


template <typename T, class queueType>
size_t WaitableQueue<T, queueType>::Size() const
{
    std::unique_lock<std::mutex> lock(this->m_mutex);
    return m_queue.size();
}


template <typename T, class queueType>
bool WaitableQueue<T, queueType>::IsEmpty() const
{
    std::unique_lock<std::mutex> lock(this->m_mutex);
    return m_queue.empty();
}

}

#endif /* __WAITABLE_QUEUE_HPP__ */