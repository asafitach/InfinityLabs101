#ifndef __FACROTY_HPP__
#define __FACROTY_HPP__

#include <map>
#include <functional>
#include <boost/core/noncopyable.hpp>  // boost::noncopyable
#include "singleton.hpp"

namespace ilrd
{
template<typename KEY, typename RETURN_TYPE, typename ARG, typename CREATOR = RETURN_TYPE(*)(ARG)>
class Factory :private boost::noncopyable
{
public:
    void RegisterCreator(KEY key, CREATOR func);
    RETURN_TYPE Create(KEY key, ARG arg);
    friend ilrd::Singleton;


private:
    std::map<KEY, CREATOR> m_map;
    Factory();

};

template<typename KEY, typename RETURN_TYPE, typename ARG, typename CREATOR>
void Factory<KEY, RETURN_TYPE, ARG, CREATOR>::RegisterCreator(KEY key, CREATOR func)
{
    m_map[key] = func;
}

template<typename KEY, typename RETURN_TYPE, typename ARG, typename CREATOR>
RETURN_TYPE Factory<KEY, RETURN_TYPE, ARG, CREATOR>::Create(KEY key, ARG arg)
{
    CREATOR *creator = NULL;
    creator = m_map.find(key);
    if(creator == m_map.end())
    {
        throw std::invalid_argument("key is invalid!\n");
    }
    return(creator(arg));
}



template<typename KEY, typename RETURN_TYPE, typename CREATOR>
class Factory<KEY, RETURN_TYPE, void, CREATOR> :private boost::noncopyable
{
public:
    void RegisterCreator(KEY key, CREATOR func);
    RETURN_TYPE Create(KEY key);


private:
    std::map<KEY, CREATOR> m_map;

};

template<typename KEY, typename RETURN_TYPE, typename CREATOR>
void Factory<KEY, RETURN_TYPE, void, CREATOR>::RegisterCreator(KEY key, CREATOR func)

{
    m_map[key] = func;
}

template<typename KEY, typename RETURN_TYPE, typename CREATOR>
RETURN_TYPE Factory<KEY, RETURN_TYPE, void, CREATOR>::Create(KEY key)

{
    CREATOR *creator = NULL;
    creator = m_map.find(key);
    if(creator == m_map.end())
    {
        throw std::invalid_argument("key is invalid!\n");
    }
    return(creator(arg));
}


}//namespace ilrd

#endif //__FACROTY_HPP__
