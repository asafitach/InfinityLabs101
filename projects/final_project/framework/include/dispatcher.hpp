#ifndef _ILRD_RD101_DISPATCHER_H
#define _ILRD_RD101_DISPATCHER_H

#include <boost/core/noncopyable.hpp>
#include <list>
#include <iostream>

namespace  ilrd
{
template <typename EVENT>
class Dispatcher;

template <typename EVENT>
class ACallback
{
public:

    explicit ACallback(Dispatcher<EVENT> *dispatcher_ptr = NULL);/* defualt arg? */
    virtual ~ACallback();//unregister to "this" - if you re-implement: call ACallback::~ACallback();

    Dispatcher<EVENT> *GetDispatcher()const;
    void SetDispatcher(Dispatcher<EVENT> *dispatcher_ptr);

    virtual void Notify(EVENT event) = 0;
    virtual void NotifyDeath();//m_dispatcher = NULL - if you re-implement: call ACallback::NotifyDeath();
private:

    Dispatcher<EVENT> *m_dispatcher;
};

/* phase 2 */
template <typename Observer, typename EVENT>
class Callback: public ACallback<EVENT>
{
public:

    Callback(void (Observer:: *notifyFunc)(EVENT), Observer *observer, Dispatcher<EVENT> *dispatcher_ptr = NULL, void (Observer:: *notifyDeath)(void) = NULL);
    virtual ~Callback();
    virtual void Notify(EVENT event); 
    virtual void NotifyDeath();
private:

    void (Observer:: *m_notifyFunc)(EVENT); 
    void (Observer:: *m_notifyDeath)(void);
    Observer *m_observer;
};

template <typename EVENT>
class Dispatcher: private boost::noncopyable
{
public:

    ~Dispatcher();
    void Register(ACallback<EVENT> *register_callback);
    void UnRegister(ACallback<EVENT> *register_callback);
    void Dispatch(EVENT event_object);

private:
    std::list<ACallback<EVENT>*> m_list_to_dispatch;
};

} // namespace  ilrd

/* templates Implementation */

namespace ilrd
{
    /* ######## Dispatcher ######## */
    template<class EVENT> 
    ilrd::Dispatcher<EVENT>::~Dispatcher()
    {
        typename std::list<ACallback<EVENT>*>::iterator iter = m_list_to_dispatch.begin();

        while (iter != m_list_to_dispatch.end())
        {
            (*iter)->NotifyDeath();
            ++iter;
        }
    }


    template<class EVENT> 
    void ilrd::Dispatcher<EVENT>::UnRegister(ilrd::ACallback<EVENT> *register_callback)
    {
        m_list_to_dispatch.remove(register_callback);
    }

    template<class EVENT> 
    void ilrd::Dispatcher<EVENT>::Register(ilrd::ACallback<EVENT> *register_callback)
    {
        register_callback->SetDispatcher(this);
        m_list_to_dispatch.push_back(register_callback);
    }

    template<class EVENT> 
    void ilrd::Dispatcher<EVENT>::Dispatch(EVENT event_object)
    {
        std::list<ACallback<EVENT>*> list_copy;
        typename std::list<ACallback<EVENT>*>::iterator iter = m_list_to_dispatch.begin();
        while (iter != m_list_to_dispatch.end())
        {
            list_copy.push_back(*iter);
            ++iter;
        }
    
        iter = list_copy.begin();
        while (iter != list_copy.end())
        {
            (*iter)->Notify(event_object);
            ++iter;
        }

    }

    /* ######## ACallback ######## */
    template<class EVENT> 
    ilrd::ACallback<EVENT>::ACallback(ilrd::Dispatcher<EVENT> *dispatcher_ptr):m_dispatcher(dispatcher_ptr)
    {
    }

    template<class EVENT> 
    ilrd::ACallback<EVENT>::~ACallback()
    {
        if (m_dispatcher)
        {
            m_dispatcher->UnRegister(this);
        }
    }

    template<class EVENT> 
    void ilrd::ACallback<EVENT>::NotifyDeath()
    {
        ACallback<EVENT>::NotifyDeath();
    }

    template<class EVENT> 
    ilrd::Dispatcher<EVENT> *ilrd::ACallback<EVENT>::GetDispatcher() const
    {
        return (m_dispatcher);
    }

    template<class EVENT> 
    void ilrd::ACallback<EVENT>::SetDispatcher(ilrd::Dispatcher<EVENT> *dispatcher_ptr)

    {
        m_dispatcher = dispatcher_ptr;
    }

    /* ######## Callback ######## */
    template<class Observer, class EVENT> 
    ilrd::Callback<Observer, EVENT>::Callback(void (Observer::*notifyFunc)(EVENT), Observer *observer, ilrd::Dispatcher<EVENT> *dispatcher_ptr, void (Observer::*notifyDeath)()): ACallback<EVENT>(dispatcher_ptr), m_notifyFunc(notifyFunc), m_notifyDeath(notifyDeath), m_observer(observer)
    {
    }


    template<class Observer, class EVENT> 
    ilrd::Callback<Observer, EVENT>::~Callback()
    {
    }

    template<class Observer, class EVENT> 
    void ilrd::Callback<Observer, EVENT>::Notify(EVENT event)
    {
        (m_observer->*m_notifyFunc)(event);
    }


    template<class Observer, class EVENT> 
    void ilrd::Callback<Observer, EVENT>::NotifyDeath()
    {
        if (!m_notifyDeath)
        {
            this->SetDispatcherToNull();
            std::cout<<"dispatcher finished - no need to wait ant longer\n";
        }
        else
        {
            (m_observer->*m_notifyDeath)();
        }
    }

} // namespace ilrd
    


#endif //_ILRD_RD101_DISPATCHER_H