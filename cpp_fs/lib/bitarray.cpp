#include <iostream>
#include "bitarray.hpp"

namespace ilrd
{
template <size_t SIZE>
typename BitArray<SIZE>::Lut BitArray<SIZE>::m_lut = Lut();

}

int main()
{
    ilrd::BitArray<80> array;

    // std::cout<<array[2000];
    array.SetAll();
    std::string str;
    array[65] = false;
    std::cout<<array[65]<<std::endl;
    array[66] = true;
    std::cout<<array[66]<<std::endl;
    str = array.ToString();
    std::cout<<str;



    return 0;
}
