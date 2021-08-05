#ifndef __DIR_MONITOR_HPP__
#define __DIR_MONITOR_HPP__

#include <boost/core/noncopyable.hpp>  // boost::noncopyable
#include <string>         // std::string
#include <thread>         // std::thread
#include "dispatcher.hpp" 

namespace ilrd
{

class DirMonitor : private boost::noncopyable
{
public:
    explicit DirMonitor(const std::string& monitoredDirPath);  // opens thread
    ~DirMonitor() noexcept;
    void Register(ACallback<const std::string&> *callback);
    void Unregister(ACallback<const std::string&> *callback);

private:
    static void Monitor(void);

    Dispatcher<const std::string&> m_dispatcher;
    const std::string m_monitoredDirPath;
    bool m_stopFlag;
    std::thread m_monitorThread;
};

}//ilrd


#endif //__DIR_MONITOR_HPP__