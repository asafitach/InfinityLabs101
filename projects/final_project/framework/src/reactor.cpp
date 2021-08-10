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
        std::list<ModeAndFd>::iterator list_iter = list.begin();
        while (iter != m_map.end())
        {
            list.push_back(iter->first);
            ++iter;
        }

        std::map<ilrd::Reactor::ModeAndFd, ilrd::Reactor::CallbackFunc> tmpMap = m_map;
        ret_list = m_platformDependentCode->Listen(list);
        list_iter = ret_list.begin();
        std::function<void(int)> funPtr;

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

std::__cxx11::list<ilrd::Reactor::ModeAndFd> ilrd::LinuxReactorPlatform::Listen(std::__cxx11::list<ilrd::Reactor::ModeAndFd> list)
{
    static const size_t EVENT_BUF_LEN = 1024;
    static const size_t G_S_TIMEOUT = 7;
    int max_fd = 0;
    char buffer[EVENT_BUF_LEN];

    struct timeval timeout;
    fd_set fd_arr[3];

    std::list<Reactor::ModeAndFd> ret_list;
    std::list<Reactor::ModeAndFd>::iterator iter = list.begin();

    bzero(buffer, EVENT_BUF_LEN); 
    FD_ZERO(&fd_arr[0]);
    FD_ZERO(&fd_arr[1]);
    FD_ZERO(&fd_arr[2]);

    while (iter != list.end())
    {
        FD_SET(iter->first, &fd_arr[iter->second]);
        max_fd = (max_fd > iter->first) ? max_fd: iter->first;
        ++iter;
    }
    
    timeout.tv_sec = G_S_TIMEOUT;
    timeout.tv_usec = 0;
    int retVal = select(max_fd + 1, &fd_arr[0], &fd_arr[1], &fd_arr[2], &timeout);

    if (-1 == retVal)
    {
        perror("select error");
    }

    iter = list.begin();
    while (iter != list.end())
    {
        if (FD_ISSET(iter->first, &fd_arr[iter->second]))
        {
            ret_list.push_back(*iter);
        }
        ++iter;
    }

    return (ret_list);
}
