#ifndef _ILRD_RD101_SINGLETON_H
#define _ILRD_RD101_SINGLETON_H

#include <string>
#include <mutex>
#include <cstdlib>

namespace ilrd
{
    template<typename T>
    class Singleton
    {
    public:
        static bool isBuilt();
        static T* GetInstance();

    protected:
    private:

        Singleton(){}
        ~Singleton(){}

        static T* m_instance;
        static std::mutex m_lock;
        static void Destroy();


    };

template<typename T>
T* Singleton<T>::m_instance = 0;


template<class T> 
void ilrd::Singleton<T>::Destroy()
{
    delete m_instance;
    m_instance = reinterpret_cast<T *> (0xDEADBEEF);
}

template<typename T>
T* Singleton<T>::GetInstance() 
{
    std::unique_lock<std::mutex> tmp_lock(m_lock);
    {
        if(!m_instance)
        {
            m_instance = new T();
            atexit(Destroy);
        }
    }
    return m_instance;
}

template<typename T>
bool Singleton<T>::isBuilt() 
{
    return (m_instance != 0);
}

template <typename T>
std::mutex Singleton<T>::m_lock;

}//ilrd

#endif //_ILRD_RD101_SINGLETON_H