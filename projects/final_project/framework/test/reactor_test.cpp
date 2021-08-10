#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "reactor.hpp"
#include <string.h>
#include <boost/bind.hpp>

class StopReacting
{
private:
    ilrd::Reactor *m_reactor;
public:
    explicit StopReacting(ilrd::Reactor *reactor);
    void operator()(int fd);
};

StopReacting::StopReacting(ilrd::Reactor *reactor): m_reactor(reactor)
{
}

void StopReacting::operator()(int fd)
{
    char buf[50] = {0};
    read(0, buf, 50);
    if (!strncmp(buf, "exit", 3))
    m_reactor->Stop();
    std::cout<<buf<<std::endl;
    
    std::cout<<"hello from fd nu: "<<fd<<std::endl;
}

class PingPong
{
public:
    void operator()(int fd);
};

void PingPong::operator()(int fd)
{
    FILE *fp = fdopen(fd, "a");
    if (EOF == fgetc(fp))
    return;
    char buf[60] = {0};
    read(fd, buf, 60);
    std::cout<<buf<<std::endl;
    strcpy(buf, "reactor read the content");
    write(fd, buf, strlen(buf));


}

int main()
{
    ilrd::IReactorPlatform *linux = new ilrd::LinuxReactorPlatform();
    ilrd::Reactor react(linux);
    int fd = open("./test.txt", O_RDWR);
    PingPong ping;
    StopReacting stopFunc(&react);
    react.Register(0, ilrd::Reactor::READ, stopFunc);
    react.Register(fd, ilrd::Reactor::WRITE, ping);
    react.Register(fd, ilrd::Reactor::WRITE, boost::bind(ilrd::Reactor::Stop, &react));

    react.Run();
    
    close(fd);
    delete linux;

    return 0;
}
