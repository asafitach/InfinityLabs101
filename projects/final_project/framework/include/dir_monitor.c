/* #ifndef __DIR_MONITOR_HPP__
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

}

#endif //__DIR_MONITOR_HPP__

 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int main( int argc, char **argv ) 
{
  int length, i = 0;
  int fd;
  int wd;
  char buffer[BUF_LEN];

  fd = inotify_init();

  if ( fd < 0 ) 
  {
    perror( "inotify_init" );
  }

  wd = inotify_add_watch( fd, "/home/asafitach/Desktop", 
                         IN_MODIFY | IN_CREATE | IN_DELETE );
  length = read( fd, buffer, BUF_LEN );  

  if ( length < 0 ) 
  {
    perror( "read" );
  }  

  while ( i < length ) 
  {
    struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
    if ( event->len ) 
    {
        if ( event->mask & IN_ISDIR )
        {} 
        else
        {
            if ( event->mask & IN_CREATE ) 
            {
                printf( "The file %s was created.\n", event->name );
            }
            else if ( event->mask & IN_DELETE ) 
            {
                printf( "The file %s was deleted.\n", event->name );
            }
            else if ( event->mask & IN_MODIFY ) 
            {
                printf( "The file %s was modified.\n", event->name );
            }
        }
    }
    i += EVENT_SIZE + event->len;
  }

  ( void ) inotify_rm_watch( fd, wd );
  ( void ) close( fd );

  exit( 0 );
}