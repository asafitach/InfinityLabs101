#ifndef __ILRD_RD101_SCOPE_LOCK_HPP
#define __ILRD_RD101_SCOPE_LOCK_HPP
//#include <iostream>

namespace ilrd
{
template <class Lockable>
class scope_lock
{
public:
    scope_lock(Lockable & m) : m_mtx(m)
    {
        //std::cout<<"lock\n";
        m_mtx.lock();
    }
    ~scope_lock()
    {
        m_mtx.unlock();
        //std::cout<<"unlock\n";
    }

private:
    scope_lock(scope_lock &other);//noncopyable
    scope_lock&operator=(const scope_lock&other);//noncopyable

    Lockable & m_mtx;
};//scope_lock
}//ilrd

#endif //__ILRD_RD101_SCOPE_LOCK_HPP

/* template <class Lockable>
class scope_lock{
public:
    explicit lock(Lockable & m) : m_mtx(m), m_locked(true)
    {
        m_mtx.lock();
    }
    ~lock()
    {
        m_locked && m_mtx.unlock();
    }
    void UnLock()
    {
        m_locked && m_mtx.unlock();
        m_locked = false;
    }
private:
    lock(lock &other);//noncopyable
    lock&operator=(const lock&other);//noncopyable

    Lockable & m_mtx;
    bool m_locked;
};//scope_lock */
