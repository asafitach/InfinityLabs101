#ifndef __FACROTY_HPP__
#define __FACROTY_HPP__

#include <map>
#include <functional>
#include <boost/core/noncopyable.hpp>  // boost::noncopyable

namespace ilrd
{
template<typename KEY, typename RETURN_TYPE, typename ARG>
class Factory :private boost::noncopyable
{
public:
    void RegisterCreator(KEY key, std::function<RETURN_TYPE (ARG)> func);
    RETURN_TYPE Create(KEY key, ARG arg);


private:
    std::map<KEY, std::function<RETURN_TYPE (ARG)>> m_map;

};

template<typename KEY, typename RETURN_TYPE, typename ARG>
void Factory<KEY, RETURN_TYPE, ARG>::RegisterCreator(KEY key, std::function<RETURN_TYPE (ARG)> func)

{
    m_map[key] = func;
}

template<typename KEY, typename RETURN_TYPE, typename ARG>
RETURN_TYPE Factory<KEY, RETURN_TYPE, ARG>::Create(KEY key, ARG arg)

{
    if(m_map.find(key) == m_map.end())
    {
        throw std::invalid_argument("key is invalid!\n");
    }
    return(m_map[key](arg));
}



template<typename KEY, typename RETURN_TYPE>
class Factory<KEY, RETURN_TYPE, void> :private boost::noncopyable
{
public:
    void RegisterCreator(KEY key, std::function<RETURN_TYPE *(void)> func);
    RETURN_TYPE Create(KEY key);


private:
    std::map<KEY, std::function<RETURN_TYPE (void)>> m_map;

};

template<typename KEY, typename RETURN_TYPE>
void Factory<KEY, RETURN_TYPE, void>::RegisterCreator(KEY key, std::function<RETURN_TYPE *(void)> func)

{
    m_map[key] = func;
}

template<typename KEY, typename RETURN_TYPE>
RETURN_TYPE Factory<KEY, RETURN_TYPE, void>::Create(KEY key)

{
    if(m_map.find(key) == m_map.end())
    {
        throw std::invalid_argument("key is invalid!\n");
    }
    return(m_map[key]());
}


}//namespace ilrd

#endif //__FACROTY_HPP__
