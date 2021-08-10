#ifndef __DLL_LOADER_HPP__
#define __DLL_LOADER_HPP__

#include <string> // std::string
#include <dlfcn.h>
#include <string.h>

namespace ilrd
{

class DLLLoader
{
public:
    void Load(const std::string& libPath)
    {
        if (strcmp(".so", libPath.c_str() + strlen(libPath.c_str()) - 3))
        {
            dlopen(libPath.c_str(), RTLD_LAZY);
        }
        else
        {
            throw std::runtime_error("error in library name");
        }
    }
};

}

#endif // __DLL_LOADER_HPP__