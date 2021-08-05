#include <dlfcn.h>
#include <iostream>
#include "logger.hpp"
#include "singleton.hpp"
#include "handleton.hpp"



int main()
{
    ilrd::Logger *hendelton_log = ilrd::Handleton<ilrd::Logger>::GetInstance();
    hendelton_log->Log(time(NULL), ilrd::Logger::WARNING, "from hendelton->->->");


    /* dynamic -run time loading */
/*     void* handle = dlopen("./loggerclass.so", RTLD_LAZY);
    ilrd::Logger *(*getinst)() = (ilrd::Logger *(*)())dlsym(handle, "ilrd::Singleton<ilrd::Logger>::GetInstance"); 
    ilrd::Logger *dynamic_log = getinst();
    */

   /* static linking */
    ilrd::Logger *log = ilrd::Singleton<ilrd::Logger>::GetInstance();
   
   
    std::cout<<log<<std::endl;
    // std::cout<<log<<getinst<<std::endl;
    log->Log(time(NULL), ilrd::Logger::INFO, "First Msg!");
    // dynamic_log->Log(time(NULL), ilrd::Logger::INFO, "Second Msg! dyn");
    log->Log(time(NULL), ilrd::Logger::INFO, "Second Msg!");
    log->Log(time(NULL), ilrd::Logger::ERROR, "Last Msg!");
    log->Log(time(NULL), ilrd::Logger::ERROR, "Last Msg!");
    // dynamic_log->Log(time(NULL), ilrd::Logger::ERROR, "Last Msg! dyn");
    log->Log(time(NULL), ilrd::Logger::INFO, "Last Msg!");
    log->Log(time(NULL), ilrd::Logger::WARNING, "Last Msg!");
    {
        ilrd::Logger *logInScope = ilrd::Singleton<ilrd::Logger>::GetInstance();
        logInScope->Log(time(NULL), ilrd::Logger::WARNING, "in scope :)");
    }

    return 0;
}