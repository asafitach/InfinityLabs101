#include "string.hpp"

int main()
{
    String c1("hello");
    String c2(" world!");
    String c3;
    c3 = c2;

    std::cout<<c1.CStr()<<" ";
    std::cout<<c1.Length()<<std::endl;

    std::cout<<c2.CStr()<<" ";
    std::cout<<c2.Length()<<std::endl;

    std::cout<<c3.CStr()<<" ";
    std::cout<<c3.Length()<<std::endl;
    std::cout<<c1<<std::endl;
    std::cout<<(c1==c2)<<std::endl;
    std::cout<<(c3==c2)<<std::endl;

    return (0);
}