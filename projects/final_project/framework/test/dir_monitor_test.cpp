#include <iostream>
#include <cstdlib>
#include "dispatcher.hpp"
#include "dir_monitor.hpp"
#include "dll_loader.hpp"

class dir_monitor_test_callback1
{
private:
    /* data */
public:
    dir_monitor_test_callback1(/* args */);
    ~dir_monitor_test_callback1();
};

dir_monitor_test_callback1::dir_monitor_test_callback1(/* args */)
{
}

dir_monitor_test_callback1::~dir_monitor_test_callback1()
{
}

int main(int argc, char const *argv[])
{
    ilrd::DirMonitor monitor("/home/asafitach/Desktop");
    return 0;
}


