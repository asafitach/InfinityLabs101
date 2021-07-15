#include <iostream>
#include "bitarray.hpp"


// template <size_t SIZE>
// // class ilrd::Lut ilrd::BitArray<SIZE>::m_lut;
// typename ilrd::Lut ilrd::BitArray<SIZE>::m_lut;

int main()
{
    ilrd::BitArray<80> array;
    ilrd::BitArray<80> array2;
    ilrd::BitArray<800> big_array;
    ilrd::BitArray<800> big_array2;

    std::cout<< array.ToString()<<std::endl;
    array.SetBit(1);
    std::cout<< array.ToString()<<std::endl;
    array.SetBit(3);
    std::cout<< array.ToString()<<std::endl;
    array.SetBit(5);
    std::cout<< array.ToString()<<std::endl;
    array.SetBit(7);
    std::cout<< array.ToString()<<std::endl;
    
    array.FlipBit(7);
    std::cout<< array.ToString()<<std::endl;
    
    array.SetBit(7);
    std::cout<< array.ToString()<<std::endl;

    array.FlipAll();
    std::cout<< array.ToString()<<std::endl;
    
    array.FlipAll();
    std::cout<< array.ToString()<<std::endl;

    std::cout<<"get bit(1): "<<array.GetBit(1)<<std::endl;
    std::cout<<"get bit(0): "<<array.GetBit(0)<<std::endl;
    std::cout<<"get bit(1): "<<array.GetBit(7)<<std::endl;

    std::cout<<"count bits: "<<array.CountBitsOn()<<std::endl;
    std::cout<< array.ToString()<<std::endl;
    // array.UnSetBit(1);
    // std::cout<<"count bits: "<<array.CountBitsOn()<<std::endl;
    // std::cout<< array.ToString()<<std::endl;
    // array.UnSetBit(3);
    // std::cout<<"count bits: "<<array.CountBitsOn()<<std::endl;
    // std::cout<< array.ToString()<<std::endl;
    // array.UnSetBit(5);
    // std::cout<<"count bits: "<<array.CountBitsOn()<<std::endl;
    // std::cout<< array.ToString()<<std::endl;
    // array.UnSetBit(7);
    // std::cout<<"count bits: "<<array.CountBitsOn()<<std::endl;
    // std::cout<< array.ToString()<<std::endl;
    

    array2 &= array;
    std::cout<<"all zero"<<std::endl;
    std::cout<< array2.ToString()<<std::endl;
    array2.SetAll();
    array2 ^= array;
    std::cout<<"xor with array1"<<std::endl;
    std::cout<< array2.ToString()<<std::endl;
    array2 &= array;
    array2 |= array;
    std::cout<<"same as array1"<<std::endl;
    std::cout<< array2.ToString()<<std::endl;
    
    array2.UnSetAll();
    array2 = array;
    std::cout<< "compare arrays\n" <<array2.ToString()<<std::endl;
    std::cout<< array.ToString()<<std::endl;
    
    std::cout<<"set all"<<std::endl;
    array2.SetAll();
    std::cout<< array2.ToString()<<std::endl;
    std::cout<<"unset all"<<std::endl;
    array2.SetAll(true);
    std::cout<< array2.ToString()<<std::endl;
    
    std::cout<<"array 1"<<std::endl;
    std::cout<< array.ToString()<<std::endl;


    if (array[1])
    {
        std::cout<<"[] operator + boolian operation is on\n";
    }
    array[0] = array[1];
    array[75] = array[1];
    array[76] = array[1];
    array[77] = array[1];
    array[78] = array[1];
    array[79] = 1;
    array[11] = true;
    array[12] = true;
    array[13] = true;
    std::cout<< array.ToString()<<std::endl;








/*
    // std::cout<<array[2000];
    array.SetAll();
    array[30] = false;
    array[60] = false;
    array[120] = false;
    array[153] = false;
    array[3] = false;
    array[6] = false;
    array[77] = false;
    array[65] = false;
    std::cout<<array[65]<<std::endl;
    array[6] = true;
    std::cout<<array[66]<<std::endl;
    std::string str;
    array2.UnSetAll();
    array.UnSetAll();
    // array.FlipAll();
    array.FlipBit(12);
    array.FlipBit(14);
    array.FlipBit(16);
    array.SetBit(8);
    array.SetBit(2);
    array.SetBit(22);
    array.SetBit(6);
    // array.FlipBit(12);
    // array.FlipBit(14);
    // array.FlipBit(16);
    array.SetBit(8, true);
    array.SetBit(122, true);
    array.SetBit(126, true);
    str = array.ToString();
    // array2 = array;
    array2.UnSetAll();

    std::string str2 = array2.ToString();
   
    std::cout<<str<<std::endl;
    std::cout<<str2<<std::endl;
    std::cout<<"count bits: "<<array.CountBitsOn()<<std::endl;
    std::cout<< (array == array2) <<std::endl;
    std::cout<< (array != array2) <<std::endl;

*/

    return 0;
}
