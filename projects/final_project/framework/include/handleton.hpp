#ifndef _ILRD_RD101_HANDLETON_H
#define _ILRD_RD101_HANDLETON_H

#include <string>
#include <mutex>
#include <cstdlib>
#include <memory>
#include <sys/ipc.h>
#include <sys/shm.h>

namespace ilrd
{
#ifdef THIS_IS_THE_ONLY_SINGLETON_IMPLEMENTATION
#define INSTANTIATE(T) template class ilrd::Handleton<T>

    template<typename T>
    class Handleton
    {
    public:
        static bool isBuilt();
        static T* GetInstance();
        static void GetTemplatedFunction()
        {}

    protected:
    private:

        Handleton(){}
        ~Handleton(){}

        static T* m_instance;
        static std::mutex m_lock;
        static void buildInstance();
        static void Destroy();


    };

/* #define INSTANTIATE(T) template class Handleton<T>
ilrd::Handleton<T>::GetTemplatedFunction()  */


/* #define INISTASIATE(T) 
template <typename T>*/

template<typename T>
T* Handleton<T>::m_instance = 0;

template<typename T>
void Handleton<T>::buildInstance()
{
    std::unique_lock<std::mutex> tmp_lock(m_lock);
    {
        if(!m_instance)
        {
            m_instance = new T();
            atexit(Destroy);
        }
    }
}

template<class T> 
void ilrd::Handleton<T>::Destroy()
{
    delete m_instance;
    m_instance = reinterpret_cast<T *> (0xDEADBEEF);
}

template<typename T>
T* Handleton<T>::GetInstance() 
{
    if ( ! isBuilt() )
      buildInstance();

    return m_instance;
}

template<typename T>
bool Handleton<T>::isBuilt() 
{
    return (m_instance != 0);
}

template <typename T>
std::mutex Handleton<T>::m_lock;


#else
    template<typename T>
    class Handleton
    {
    public:
        static T* GetInstance();
    private:
        Handleton(){}
    };
#endif
}//ilrd

#endif //_ILRD_RD101_HANDLETON_H