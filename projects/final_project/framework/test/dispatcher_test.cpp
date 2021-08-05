#include <iostream>
#include "dispatcher.hpp"

using namespace std; 
using namespace ilrd; 

enum Event {ON, GO, OFF}; 

template <typename EVENT>
class EventCallBack : public ACallback<EVENT>
{
public:

    explicit EventCallBack(Dispatcher<EVENT> *dispatcher_ptr) : ACallback<EVENT>(dispatcher_ptr){}
    virtual void Notify(EVENT event) {cout << "event has accurde" << endl;event = event;}
    virtual void NotifyDeath() {cout << "dipacher is dead" << endl; this->SetDispatcherToNull();}
    ~EventCallBack() {if (ACallback<EVENT>::GetDispatcher()){Dispatcher<EVENT> *Dispatcher = ACallback<EVENT>::GetDispatcher(); Dispatcher->UnRegister(this);}}
private:
    bool death_flag; 
};



class Observer 
{
public:
    virtual void Notify(Event event) {cout << "Observer has accurde" << endl;event = event;}
    virtual void NotifyDeath() {cout << "Observer: dipacher is dead" << endl;}
    virtual ~Observer(){}

private:
    bool death_flag; 
};


int main()
{
    Dispatcher<Event> *event_dispacher = new Dispatcher<Event>; 

    ACallback<Event> *dipatcher_class = new EventCallBack<Event>(event_dispacher); 
    
    event_dispacher->Register(dipatcher_class); 

    event_dispacher->Dispatch(ON); 

    delete event_dispacher; 

    delete dipatcher_class;

    /********************************************************************/

    Dispatcher<Event> *g_dispacher = new Dispatcher<Event>;
 
    Observer *observer_object = new Observer();

    ACallback<Event> *callback_obj = new Callback<Observer, Event>(&Observer::Notify, observer_object, g_dispacher, &Observer::NotifyDeath); 
    
    g_dispacher->Register(callback_obj); 

    g_dispacher->Dispatch(ON); 

    delete callback_obj;

    delete observer_object;

    delete g_dispacher;

    return (0); 
}