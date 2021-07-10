#ifndef ILRD__RD101_BIT_ARRAY_HPP
#define ILRD__RD101_BIT_ARRAY_HPP

#include <string>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>

namespace ilrd
{

static const size_t WORD_SIZE  = sizeof(size_t);

template <size_t SIZE = WORD_SIZE>
class BitArray
{
private:
    static const size_t BITS_IN_BYTE = 8;
    static const size_t LUT_SIZE = 256;
    static const size_t SIZE_IN_SIZE_T = ((SIZE - 1) / (BITS_IN_BYTE * WORD_SIZE)) + 1;
    class BitProxy;
    class Lut;

public:
    explicit BitArray();
    BitProxy operator[](size_t index);/* can throw exception "out_of_range" */
    bool operator[](size_t index) const;/* can throw exception "out_of_range" */

    bool operator==(const BitArray &other) const;
    bool operator!=(const BitArray &other) const;

    BitArray& operator &=(const BitArray &other);
    BitArray& operator ^=(const BitArray &other);
    BitArray& operator |=(const BitArray &other);
    BitArray& operator <<=(size_t n_times);//advanced
    BitArray& operator >>=(size_t n_times);//advanced

    BitArray& SetBit(size_t index, bool setTo = true);/* can throw exception "out_of_range" */
    BitArray& UnSetBit(size_t index);/* can throw exception "out_of_range" */
    BitArray& SetAll(bool setTo = true);
    BitArray& UnSetAll();
    bool GetBit(size_t index)const;/* can throw exception out_of_range */
    void FlipBit(size_t index);/* can throw exception out_of_range */
    void FlipAll();
    size_t CountBitsOn()const;

    std::string ToString() const;

private:
    size_t m_array[SIZE_IN_SIZE_T];
    static Lut m_lut;

    class Lut
    {
    public:
        Lut()
        {
            for (size_t i = 0; i < 256; i++)
            {
                lut[i] = i & 1 + lut[i / 2];
            }
            
        }
        char GetBitsOn(size_t num)
        {
            return (lut[num]);
        }

    private:
        char lut[LUT_SIZE];
    };

    class BitProxy
    {
    public:
        explicit BitProxy(size_t &array, size_t index);
        virtual ~BitProxy();
        BitProxy& operator=(const BitProxy &other);
        BitProxy& operator=(bool changeTo);
        operator bool() const;

    private:
        size_t &m_bitSet;   
        size_t m_index;
    };//BitProxy
    
    
};//BitArray<SIZE>



class SetZero
{
public:
    void operator()(size_t& x)
    {
        x = 0;
    }
};

class SetAll
{
public:
    void operator()(size_t& x)
    {
        x = 0xffffffffffffffff;
    }
};


class CmpSize_t
{
public:
    bool operator()(size_t m1,  size_t m2)
    {
        return (m1 == m2);
    }

};


template <size_t SIZE> 
BitArray<SIZE>::BitArray()
{
    std::for_each(m_array, m_array + SIZE_IN_SIZE_T, SetZero());
}


template<size_t SIZE>
typename BitArray<SIZE>::BitProxy BitArray<SIZE>::operator[](size_t index)
{
    return BitProxy(m_array[index / BITS_IN_BYTE * WORD_SIZE], index % (BITS_IN_BYTE * WORD_SIZE));
}


template <size_t SIZE> 
bool BitArray<SIZE>:: operator[](size_t index) const
{
    return m_array[index / BITS_IN_BYTE] & 1 << (index % BITS_IN_BYTE);
}
template <size_t SIZE> 
bool BitArray<SIZE>:: operator==(const BitArray &other) const
{
    return(
    std::lexicographical_compare(m_array, m_array + SIZE_IN_SIZE_T, other.m_array, other.m_array + SIZE_IN_SIZE_T, CmpSize_t()));

}


template <size_t SIZE> 
bool BitArray<SIZE>:: operator!=(const BitArray &other) const
{
    return true;
}


template <size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>::operator &=(const BitArray<SIZE> &other)
{
    return *this;

}
template <size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>::operator ^=(const BitArray<SIZE> &other)
{
    return *this;

}


template <size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>::operator |=(const BitArray<SIZE> &other)
{
    return *this;

}
// template <size_t SIZE> 
// BitArray<SIZE> &BitArray<SIZE>::operator <<=(size_t n_times)
// template <size_t SIZE> 
// BitArray<SIZE> &BitArray<SIZE>::operator >>=(size_t n_times)



template <size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>::SetBit(size_t index, bool setTo)
{
    m_array[index / BITS_IN_BYTE] &= ~(1 << index);
    
    if (!setTo)
    {
        m_array[index / BITS_IN_BYTE] |= (1 << index);
    }
    return *this;
}

template <size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>::UnSetBit(size_t index)
{
    return (SetBit(index, false));
}


template<size_t SIZE> 
BitArray<SIZE> &BitArray<SIZE>::SetAll(bool setTo)
{
    if (setTo)
    {
        // std::for_each(m_array, m_array + SIZE_IN_SIZE_T, SetAll());
        for (size_t i = 0; i < SIZE_IN_SIZE_T; ++i)
        {
            m_array[i] = 0xffffffffffffffff;
        }
    }
    else
    {
        // std::for_each(m_array, m_array + SIZE_IN_SIZE_T, SetZero());
        for (size_t i = 0; i < SIZE_IN_SIZE_T; ++i)
        {
            m_array[i] = 0;
        }
    }
    return *this;
}

template <size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>:: UnSetAll()
{
    std::for_each(m_array, m_array + SIZE_IN_SIZE_T, SetZero());
    return *this;
}

template <size_t SIZE> 
bool BitArray<SIZE>:: GetBit(size_t index)const
{
    return (m_array[index / BITS_IN_BYTE] & (1 << (index % BITS_IN_BYTE)));
}

template <size_t SIZE> 
void BitArray<SIZE>:: FlipBit(size_t index)
{
    m_array[index / BITS_IN_BYTE] ^= (1 << (index % BITS_IN_BYTE));
}

template <size_t SIZE> 
void BitArray<SIZE>:: FlipAll()
{
    for (int i = SIZE_IN_SIZE_T/* -1 */; i >= 0; --i)
    {
        m_array[i] ^= 0xffffffffffffffff;
    }
}

template <size_t SIZE> 
size_t BitArray<SIZE>:: CountBitsOn()const
{
    size_t counter = 0;
    char *runner = static_cast<char *>(m_array);
    for (int i = 0; i < SIZE_IN_SIZE_T * BITS_IN_BYTE; ++i, ++runner)
    {
        counter += m_lut.GetBitsOn();
    }
     return (counter);
}
template <size_t SIZE> 
std::string BitArray<SIZE>:: ToString() const
{
    char tmp[SIZE_IN_SIZE_T * BITS_IN_BYTE * WORD_SIZE + 1] = {0};

    // for (int i = SIZE_IN_SIZE_T/* -1 */; i >= 0; --i)
    // {
    //     for (int j = BITS_IN_BYTE - 1; j >= 0; --j)
    //     {
    //         str[i * BITS_IN_BYTE + j] = '0' + (m_array[i] & (1 << j));
    //     }
    // }

    size_t counter = 0;
    for (size_t index = 0; index < SIZE_IN_SIZE_T; ++index)
    {
        for (size_t j = 0; j < BITS_IN_BYTE * WORD_SIZE; ++j, ++counter)
        {
            tmp[counter] = '0' + ((m_array[index] >> j) & 1);
        }
    }
    tmp[SIZE_IN_SIZE_T * BITS_IN_BYTE * WORD_SIZE] = 0;

    std::string str(tmp);
    return (str);
}



// class functor
// {
// public:
//     functor(/* args */);
//     ~functor();
//     operator()();
// private:
//     /* data */
// };



template<size_t SIZE> ilrd::BitArray<SIZE>::BitProxy::BitProxy(size_t &array, size_t index): m_bitSet(array), m_index(index)
{
}
template<size_t SIZE> ilrd::BitArray<SIZE>::BitProxy::~BitProxy()
{
}
template<size_t SIZE> typename ilrd::BitArray<SIZE>::BitProxy &ilrd::BitArray<SIZE>::BitProxy::operator=(const ilrd::BitArray<SIZE>::BitProxy &other)
{
    m_bitSet &= ~(1 << m_index);
    m_bitSet |= (other.m_bitSet >> other.m_index) & 1;
    return (*this);
    // m_bitSet = other.m_bitSet;
    // m_index = other.m_index;
}
template<size_t SIZE> typename ilrd::BitArray<SIZE>::BitProxy &ilrd::BitArray<SIZE>::BitProxy::operator=(bool changeTo)
{
    m_bitSet &= ~(1 << m_index);
    m_bitSet |= changeTo << m_index;
    return (*this);
}
template<size_t SIZE> ilrd::BitArray<SIZE>::BitProxy::operator bool() const
{
    return (m_bitSet >> m_index) & 1;
}




/*


BitProxy &BitArray<size>::operator[](int index)
{
    BitProxy prox(m_array[BYTE_TO_RERFER(index)], index % BYTE);
    return (prox);
}

*/

}//ilrd
#endif// ILRD__RD101_BIT_ARRAY_HPP
