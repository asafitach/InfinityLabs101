#ifndef ILRD__RD101_BIT_ARRAY_HPP
#define ILRD__RD101_BIT_ARRAY_HPP

#include <string>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <cstdlib>

inline void TrowFunc()
{
    throw std::out_of_range ("too big index");
}

namespace ilrd
{

class Lut;
static const size_t WORD_SIZE  = sizeof(size_t);
static const size_t LUT_SIZE = 256;
static const size_t BITS_IN_BYTE = 8;

template <size_t SIZE = WORD_SIZE>
class BitArray
{
private:
    static const size_t SIZE_IN_SIZE_T = ((SIZE - 1) / (BITS_IN_BYTE * WORD_SIZE)) + 1;
    class BitProxy; // the user recieve BitProxy from operator[] so this class being private is pointless

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
    
    template <size_t LUT_SIZE> 
    friend class FunctorGentBitsOn;

private:
    size_t m_array[SIZE_IN_SIZE_T];
    static Lut m_lut;

    class BitProxy
    {
    public:
        BitProxy(size_t &array, size_t index);
        BitProxy(BitProxy &other);
        virtual ~BitProxy();
        BitProxy& operator=(const BitProxy &other);//can be deleted
        BitProxy& operator=(bool changeTo);
        operator bool() const;

    private:
        size_t &m_bitSet;
        size_t m_index;
    };//BitProxy
    
    
};//BitArray<SIZE>

class Lut
{
public:
    Lut();
    size_t GetBitsOn(size_t num);
private:
    char lut[LUT_SIZE];
};

Lut::Lut()
{
    for (size_t i = 0; i < LUT_SIZE; i++) 
    {
        lut[i] = (i & 1) + lut[i / 2];/* takes the bits on from the prev power of 2 (i / 2) and adds one if lsb is on */
    }
}

size_t Lut::GetBitsOn(size_t num)
{
    size_t mask = 0xff;
    return (lut[num & mask]
            +lut[mask & (num >> BITS_IN_BYTE)]
            +lut[mask & (num >> (BITS_IN_BYTE * 2))]
            +lut[mask & (num >> (BITS_IN_BYTE * 3))]
            +lut[mask & (num >> (BITS_IN_BYTE * 4))]
            +lut[mask & (num >> (BITS_IN_BYTE * 5))]
            +lut[mask & (num >> (BITS_IN_BYTE * 6))]
            +lut[mask & (num >> (BITS_IN_BYTE * 7))]);
}

class SetZero
{
public:
    void operator()(size_t& x)
    {
        x = 0;
    }
};

class FlipBitsFunctor
{
public:
    void operator()(size_t& x)
    {
        x ^= 0xffffffffffffffff; //(size_t)-1 or ~0LU is also gooood
    }
};

class SetAllFunctor
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


class OrFunctor
{
public:
    size_t operator() (size_t &left, const size_t &right)
    {
        left |= right;
        return (left);
    }
};

class XorFunctor
{
public:
    size_t operator() (size_t &left, const size_t &right)
    {
        left ^= right;
        return (left);
    }
};

class AndFunctor
{
public:
    size_t operator() (size_t &left, const size_t &right)
    {
        left &= right;
        return (left);
    }
};

template <size_t SIZE> 
class FunctorGentBitsOn 
{
    public:
        FunctorGentBitsOn() {}
        
        size_t operator() (size_t ans, const size_t &x)
        {
            ans += BitArray<SIZE>::BitArray::m_lut.GetBitsOn(x);
            return ans; 
        }
}; 



template <size_t SIZE> 
BitArray<SIZE>::BitArray()
{
    SetAll(false);
//    std::for_each(m_array, m_array + SIZE_IN_SIZE_T, SetZero());//calling setAll possible also
}


template<size_t SIZE>
typename BitArray<SIZE>::BitProxy BitArray<SIZE>::operator[](size_t index)
{
    if (index >= SIZE)
    {
        TrowFunc();
    }
    BitProxy tmp(m_array[index / (BITS_IN_BYTE * WORD_SIZE)], index % (BITS_IN_BYTE * WORD_SIZE));
    return tmp;
}


template <size_t SIZE> 
bool BitArray<SIZE>:: operator[](size_t index) const
{
    if (index >= SIZE)
    {
        TrowFunc();
    }
    return m_array[index / (BITS_IN_BYTE * WORD_SIZE)] & 1 << (index % (BITS_IN_BYTE * WORD_SIZE));
}

template <size_t SIZE> 
bool BitArray<SIZE>:: operator==(const BitArray &other) const
{
    return (std::equal(m_array, m_array + SIZE_IN_SIZE_T, other.m_array));
}

template <size_t SIZE> 
bool BitArray<SIZE>:: operator!=(const BitArray &other) const
{
    return !(*this == other);
}


template <size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>::operator |= (const BitArray &other)
{
    std::transform(m_array, m_array + SIZE_IN_SIZE_T, other.m_array, m_array, OrFunctor());
    return *this; 
}


template <size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>::operator ^=(const BitArray &other)
{
    std::transform(m_array, m_array + SIZE_IN_SIZE_T, other.m_array, m_array, XorFunctor());
    return *this; 
}


template <size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>::operator &=(const BitArray &other)
{
    std::transform(m_array, m_array + SIZE_IN_SIZE_T, other.m_array, m_array, AndFunctor());
    return *this; 
}


// template <size_t SIZE> 
// BitArray<SIZE> &BitArray<SIZE>::operator <<=(size_t n_times)
// template <size_t SIZE> 
// BitArray<SIZE> &BitArray<SIZE>::operator >>=(size_t n_times)



template <size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>::SetBit(size_t index, bool setTo)
{
    if (index >= SIZE)
    {
        TrowFunc();
    }
    
    if (false == setTo)
    {
        m_array[index / (BITS_IN_BYTE * WORD_SIZE)] &= ~(1 << index);
    }
    
    else
    {
        m_array[index / (BITS_IN_BYTE * WORD_SIZE)] |= (1 << index);
    }
    return *this;
}

template <size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>::UnSetBit(size_t index)
{
    if (index >= SIZE)
    {
        TrowFunc();
    }
    return (SetBit(index, false));
}


template<size_t SIZE> 
BitArray<SIZE> &BitArray<SIZE>::SetAll(bool setTo)
{
    if (false == setTo)
    {
        std::for_each(m_array, m_array + SIZE_IN_SIZE_T, SetZero());
    }
    else
    {
        std::for_each(m_array, m_array + SIZE_IN_SIZE_T, SetAllFunctor());
    }
    return *this;
}

template <size_t SIZE> 
BitArray<SIZE>& BitArray<SIZE>:: UnSetAll()
{
    return SetAll(false);
}

template <size_t SIZE> 
bool BitArray<SIZE>:: GetBit(size_t index)const
{
    if (index >= SIZE)
    {
        TrowFunc();
    }
    return (m_array[index]);
    //return (m_array[index / (BITS_IN_BYTE * WORD_SIZE)] & (1 << (index % (BITS_IN_BYTE * WORD_SIZE))));
}

template <size_t SIZE> 
void BitArray<SIZE>:: FlipBit(size_t index)
{
    if (index >= SIZE)
    {
        TrowFunc();
    }
    m_array[index / (BITS_IN_BYTE * WORD_SIZE)] ^= (1 << (index % (BITS_IN_BYTE * WORD_SIZE)));
}

template <size_t SIZE> 
void BitArray<SIZE>:: FlipAll()
{
    std::for_each(m_array, m_array + SIZE_IN_SIZE_T, FlipBitsFunctor());
}

template <size_t SIZE> 
size_t BitArray<SIZE>::CountBitsOn() const
{
    size_t ans = 0; 
    
    return (std::accumulate (m_array, m_array + SIZE_IN_SIZE_T, ans, FunctorGentBitsOn<SIZE>()));  
}

template <size_t SIZE> 
std::string BitArray<SIZE>:: ToString() const
{
    char tmp[SIZE_IN_SIZE_T * BITS_IN_BYTE * WORD_SIZE + 1] = {0};
    size_t counter = SIZE - 1;

    for (size_t index = 0; index < SIZE_IN_SIZE_T; ++index)
    {
        for (size_t j = 0; j < BITS_IN_BYTE * WORD_SIZE; ++j, --counter)
        {
            tmp[counter] = '0' + ((m_array[index] >> j) & 1);
        }
    }

    tmp[SIZE] = 0;

    std::string str(tmp);
    return (str);
}



template<size_t SIZE> BitArray<SIZE>::BitProxy::BitProxy(size_t &array, size_t index): m_bitSet(array), m_index(index)
{
}
template<size_t SIZE> BitArray<SIZE>::BitProxy::BitProxy(BitProxy& other): m_bitSet(other.m_bitSet), m_index(other.m_index)
{
}
template<size_t SIZE> BitArray<SIZE>::BitProxy::~BitProxy()
{
}
template<size_t SIZE> typename BitArray<SIZE>::BitProxy &BitArray<SIZE>::BitProxy::operator=(const BitArray<SIZE>::BitProxy &other)
{
    bool tmp = static_cast<bool>(((other.m_bitSet) >> other.m_index) & 1);
    return (*this = tmp);
}
template<size_t SIZE> typename BitArray<SIZE>::BitProxy &BitArray<SIZE>::BitProxy::operator=(bool changeTo)
{
    m_bitSet &= ~(1 << m_index);
    m_bitSet |= (changeTo) << m_index;
    return (*this);
}
template<size_t SIZE> BitArray<SIZE>::BitProxy::operator bool() const
{
    return ((m_bitSet >> m_index) & 1);
}


template <size_t SIZE>
typename ilrd::Lut ilrd::BitArray<SIZE>::m_lut;


}//ilrd

#endif// ILRD__RD101_BIT_ARRAY_HPP
