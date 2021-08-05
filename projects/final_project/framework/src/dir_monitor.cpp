#include "dispatcher.hpp"
#include "dir_monitor.hpp"



ilrd::DirMonitor::DirMonitor(const std::string &monitoredDirPath):m_monitoredDirPath(monitoredDirPath), m_stopFlag(false), m_dispatcher(), m_monitorThread(Monitor)
{
}

ilrd::DirMonitor::~DirMonitor() noexcept
{

}

void ilrd::DirMonitor::Register(ilrd::ACallback<const std::string &> *callback)
{

}

void ilrd::DirMonitor::Unregister(ilrd::ACallback<const std::string &> *callback)
{

}

void ilrd::DirMonitor::Monitor()
{

}
