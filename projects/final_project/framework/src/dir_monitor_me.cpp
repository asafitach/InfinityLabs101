#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include "dispatcher.hpp"
#include "dir_monitor.hpp"
#include <memory>
#include <string.h>


#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )


ilrd::DirMonitor::DirMonitor(const std::string &monitoredDirPath):m_monitoredDirPath(monitoredDirPath), m_stopFlag(false), m_monitorThread(std::thread(Monitor, this))
{
}

ilrd::DirMonitor::~DirMonitor() 
{
	m_stopFlag = true;
    m_monitorThread.join();
}

void ilrd::DirMonitor::Register(ilrd::ACallback<const std::string &> *callback)
{
    m_dispatcher.Register(callback);
}

void ilrd::DirMonitor::Unregister(ilrd::ACallback<const std::string &> *callback)
{
    m_dispatcher.UnRegister(callback);
}


void ilrd::DirMonitor::Monitor(DirMonitor *monitored_file)
{
	int length = 0; 
	int i = 0;
	int fd;
	int wd;
	char buffer[BUF_LEN];

	fd = inotify_init();

	if (fd < 0)
	{
		perror("inotify_init");
	}

	wd = inotify_add_watch(fd, monitored_file->m_monitoredDirPath.c_str(), IN_CREATE | IN_DELETE);

	struct inotify_event *event = {0};

	while (false == monitored_file->m_stopFlag) 
	{
		length = read(fd, buffer + i, BUF_LEN);
		if (length < 0)

		{
		  perror("read");
		}
		event = (struct inotify_event *) &buffer[i];	
		if (event->mask & IN_CREATE || event->mask & IN_DELETE /* || event->mask & IN_MODIFY */)
		{
		    if (event->mask & IN_CREATE)
		    {
		        monitored_file->m_dispatcher.Dispatch("create");
		        printf("The file %s was created.\n", event->name);
		    }
/* 		    else if (event->mask & IN_MODIFY) 
		    {
		        monitored_file->m_dispatcher.Dispatch("modify");
		        printf( "The file %s was modified.\n", event->name );
		    } */
		    else
		    {
		        monitored_file->m_dispatcher.Dispatch("delete");
		        printf( "The file %s was deleted.\n", event->name );
		    }
		}	
		  // memset(buffer, 0, BUF_LEN);
		  // i = 0;
		i += EVENT_SIZE + event->len;
	}

	(void) inotify_rm_watch(fd, wd);
	(void) close(fd);

}
