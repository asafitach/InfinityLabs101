#ifndef __LINUX_LISTERNER_
#define __LINUX_LISTERNER_

#include "reactor.hpp"

namespace ilrd
{

class LinuxReactorPlatform: public IReactorPlatform 
{
public:
    virtual std::list<Reactor::ModeAndFd> Listen(std::list<Reactor::ModeAndFd>); 
    virtual ~LinuxReactorPlatform(){}
};

}

#endif //__LINUX_LISTERNER_