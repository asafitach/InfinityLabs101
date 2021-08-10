#include <sys/inotify.h>
#include <sys/time.h>
#include <strings.h>
#include "dir_monitor.hpp"

namespace ilrd
{


DirMonitor::DirMonitor(const std::string& monitoredDirPath) : 
    m_monitoredDirPath(monitoredDirPath), m_monitorThread(std::thread(DirMonitor::Monitor,this)), m_stopFlag(false)
{

}  

void DirMonitor::Monitor(DirMonitor *dirMonitor)
{
    static const size_t EVENT_SIZE = sizeof(struct inotify_event);
    static const size_t EVENT_BUF_LEN = 1024;  
    static const size_t G_S_TIMEOUT = 7; 
    
    char buffer[EVENT_BUF_LEN];
    
    int inotifyFd = inotify_init();
    if (inotifyFd < 0) 
    {
        perror( "inotify_init" ); 
    }
    
    int wd = inotify_add_watch(inotifyFd, dirMonitor->m_monitoredDirPath.c_str(), IN_CREATE | IN_DELETE);

    if (0 < wd)
    {
        perror("inotify_add");
    }

    struct timeval timeout;
    fd_set readSet;

    while (!(dirMonitor->m_stopFlag)) 
    {
        bzero(buffer, EVENT_BUF_LEN); 

        FD_ZERO(&readSet);
        FD_SET(inotifyFd, &readSet);
        
        timeout.tv_sec = G_S_TIMEOUT;
        timeout.tv_usec = 0;

        int retVal = select(inotifyFd + 1, &readSet, NULL, NULL, &timeout);
        
        if (-1 == retVal)
        {
            perror("select error");
        }

        int i = 0;
        
        if (i < retVal)
        {
            int length = read(inotifyFd, buffer, EVENT_BUF_LEN);
            
            while (i < length)
            { 
                struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];     
                
                if (event->len) 
                {
                    dirMonitor->m_dispatcher.Dispatch(dirMonitor->m_monitoredDirPath + "/" + event->name); 
                }
            
                i += EVENT_SIZE + event->len;
            }
    
        }

    }
    //closing the INOTIFY instance
    inotify_rm_watch(inotifyFd, wd);
    close(inotifyFd);
}


DirMonitor::~DirMonitor() noexcept 
{
    m_stopFlag = true; 
    m_monitorThread.join(); 
}

void DirMonitor::Register(ACallback<const std::string&> *callback)
{
    m_dispatcher.Register(callback); 
}

void DirMonitor::Unregister(ACallback<const std::string&> *callback)
{
    m_dispatcher.UnRegister(callback); 
}


}




