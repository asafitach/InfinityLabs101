#include "linux_listener.hpp"

std::__cxx11::list<ilrd::Reactor::ModeAndFd> ilrd::LinuxReactorPlatform::Listen(std::__cxx11::list<ilrd::Reactor::ModeAndFd> list)
{
    static const size_t EVENT_BUF_LEN = 1024;
    static const size_t G_S_TIMEOUT = 7;
    
    int max_fd = 0;
    char buffer[EVENT_BUF_LEN];
    fd_set fd_arr[3];

    memset(buffer, 0, EVENT_BUF_LEN); 
    FD_ZERO(&fd_arr[0]);
    FD_ZERO(&fd_arr[1]);
    FD_ZERO(&fd_arr[2]);

    std::list<Reactor::ModeAndFd>::iterator iter = list.begin();
    while (iter != list.end())
    {
        FD_SET(iter->first, &fd_arr[iter->second]);
        max_fd = (max_fd > iter->first) ? max_fd: iter->first;
        ++iter;
    }
    
    struct timeval timeout;
    timeout.tv_sec = G_S_TIMEOUT;
    timeout.tv_usec = 0;
    int retVal = select(max_fd + 1, &fd_arr[0], &fd_arr[1], &fd_arr[2], &timeout);
    if (-1 == retVal)
    {
        perror("select error");
    }

    std::list<Reactor::ModeAndFd> ret_list;
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