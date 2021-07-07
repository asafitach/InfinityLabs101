#include <iostream>
#include <mutex>
#include "scope_lock.hpp"

int main()
{
    std::mutex mtx;
    ilrd::scope_lock<std::mutex> scope_lock_mutex_1(mtx);

    std::cout<<"critical section\n";
    
    return (0);
}

