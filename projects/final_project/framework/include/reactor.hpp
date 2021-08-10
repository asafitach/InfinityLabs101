#ifndef __REACTOR_HPP__
#define __REACTOR_HPP__

#include <functional>
#include <utility>
#include <map>
#include <list>
#include <boost/core/noncopyable.hpp>   // boost::noncopyable
#include <boost/function.hpp>

namespace ilrd
{

class IReactorPlatform; 

class Reactor : private boost::noncopyable 
{
public:
    enum mode_t
    {
        READ = 0,
        WRITE,
        EXCEPT
    };
    typedef std::pair<int, Reactor::mode_t> ModeAndFd;
    // typedef std::function<void(int)> CallbackFunc;
    typedef boost::function<void(int)> CallbackFunc;
    

    explicit Reactor(IReactorPlatform *platformDependentCode);

    // replaces former registration
    void Register(int fd, mode_t mode, CallbackFunc callback);
    void UnRegister(int fd, mode_t mode);

    // BlockingCall
    void Run();

    // Can be call only from callback function, not a Thread-safe
    void Stop();

private:
    bool m_toStop;
    std::map<ModeAndFd, CallbackFunc> m_map;
    IReactorPlatform *m_platformDependentCode;
};

class IReactorPlatform
{
public:
    virtual std::list<Reactor::ModeAndFd> Listen(std::list<Reactor::ModeAndFd>) = 0; 
    virtual ~IReactorPlatform(){}
};

class LinuxReactorPlatform: public IReactorPlatform 
{
public:
    virtual std::list<Reactor::ModeAndFd> Listen(std::list<Reactor::ModeAndFd>); 
    virtual ~LinuxReactorPlatform(){}
};

}//namespace ilrd

#endif /* __REACTOR_HPP__ */