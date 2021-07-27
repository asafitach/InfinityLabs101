#ifndef __WAITABLE_PRIORITY_QUEUE_H__
#define __WAITABLE_PRIORITY_QUEUE_H__

#include <queue>
#include <boost/core/noncopyable.hpp>

namespace ilrd
{

template <typename T>
class PriorityQueue : private boost::noncopyable
{
public:
    const T &front() const;
    void push(const T&data);
    void pop();
    bool empty() const;
    size_t size() const;

private:
    std::priority_queue<T> m_pqueue;
};

template <typename T>
const T & PriorityQueue<T>::front() const
{
    return m_pqueue.top();
}

template <typename T>
void PriorityQueue<T>::push(const T&data)
{
    m_pqueue.push(data);
}

template <typename T>
void PriorityQueue<T>::pop()
{
    m_pqueue.pop();
}

template <typename T>
bool PriorityQueue<T>::empty() const
{
    return m_pqueue.empty();
}

template <typename T>
size_t PriorityQueue<T>::size() const
{
    return m_pqueue.size();
}

}

#endif