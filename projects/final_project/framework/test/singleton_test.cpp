#include <iostream>
#include "singleton.hpp"


class test
{
    public:
    int GetInt()
    {
        return -32;
    }
    size_t GetSizeT()
    {
        return 12;
    }
    std::string GetStr()
    {
        return ("hello");
    }
    private:
    int x;
};

template <typename T>
class wrap
{
    public:
    wrap(ilrd::Singleton<T> *tst):m_tst(tst)
    {
        atexit(Dtor);
    }
    void Dtor()
    {
        ilrd::Singleton<T> *tmp = m_tst->GetInstance();
        std::cout<<m_tst<<std::end;
    } 

    private:
        ilrd::Singleton<T> *m_tst;
};

int main()
{
    ilrd::Singleton<test> *tst;
    test *tmp = ilrd::Singleton<test>::GetInstance();
    test *tmp1 = ilrd::Singleton<test>::GetInstance();
    test *tmp2 = ilrd::Singleton<test>::GetInstance();
    test *tmp3 = ilrd::Singleton<test>::GetInstance();
    wrap<test> tt(tst);
    std::cout<<tst->GetInstance()->GetInt()<<std::endl;
    std::cout<<tst->GetInstance()->GetSizeT()<<std::endl;
    std::cout<<tst->GetInstance()->GetStr()<<std::endl;

    return 0;
}