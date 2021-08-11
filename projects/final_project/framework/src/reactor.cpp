#include <functional>
#include <utility>
#include <map>
#include <list>
#include <string.h>
#include <boost/core/noncopyable.hpp>   // boost::noncopyable
#include "reactor.hpp"
#include <boost/bind.hpp>



ilrd::Reactor::Reactor(ilrd::IReactorPlatform *platformDependentCode): m_toStop(false), m_platformDependentCode(platformDependentCode)
{
}

void ilrd::Reactor::UnRegister(int fd, ilrd::Reactor::mode_t mode)
{
    m_map.erase(std::pair<int, Reactor::mode_t>(fd, mode));
}

void ilrd::Reactor::Register(int fd, ilrd::Reactor::mode_t mode, ilrd::Reactor::CallbackFunc callback)
{
    callback = boost::bind(ilrd::Reactor::Stop, this);
    m_map[std::pair<int, Reactor::mode_t>(fd, mode)] = callback;
}

void ilrd::Reactor::Run()
{
    std::list<ModeAndFd> list;
    std::list<ModeAndFd> ret_list;

    while (!m_toStop)
    {
        std::map<ModeAndFd, CallbackFunc>::iterator iter = m_map.begin();
        while (iter != m_map.end())
        {
            list.push_back(iter->first);
            ++iter;
        }

        std::map<ilrd::Reactor::ModeAndFd, ilrd::Reactor::CallbackFunc> tmpMap = m_map;
        ret_list = m_platformDependentCode->Listen(list);
        std::list<ModeAndFd>::iterator list_iter = ret_list.begin();

        while (list_iter != ret_list.end())
        {
            tmpMap[std::pair<int, Reactor::mode_t>(*list_iter)](list_iter->first);
            ++list_iter;
        }
    }
}

void ilrd::Reactor::Stop()
{
    m_toStop = true;
}


