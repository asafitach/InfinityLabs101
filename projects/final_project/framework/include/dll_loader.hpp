#ifndef __DLL_LOADER_HPP__
#define __DLL_LOADER_HPP__

#include <string> // std::string

namespace ilrd
{

class DLLLoader
{
public:
    void Load(const std::string& libPath);
};

}

#endif // __DLL_LOADER_HPP__