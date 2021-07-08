#ifndef ILRD__RD101_BIT_PROXY_HPP
#define ILRD__RD101_BIT_PROXY_HPP

#include <iostream>

#define BYTE_TO_RERFER(a) (a - 1) / 8

class BitProxy
{
public:
    BitProxy& operator=(bool change_to);
    bool operator+() const;
    bool operator-() const;
    bool operator&&(bool other) const;
    bool operator||(bool other) const;
    bool operator()()const;

    friend std::ostream operator<<(std::ostream os, BitProxy &prox);
protected:
    explicit BitProxy(bitarr &array, size_t index);
    virtual ~BitProxy();
private:
    char &m_byte_to_refer;
    char m_index;
};//BitProxy



BitProxy::BitProxy(bitarr &array, size_t index): 
            m_byte_to_refer(array.m_bit_array[BYTE_TO_RERFER(index)]), 
            m_index(index % 8)
{
}

BitProxy::~BitProxy()
{
}


BitProxy &BitProxy::operator=(bool change_to)
{
    /*         &   |   ^   
        0    1 0     0   1   1
        1    0 1     0   1   1
        0    1 1     1   1   0
        1    0 0     0   0   0
     */
    
    m_byte_to_refer &= ~(1 << m_index);
    m_byte_to_refer &= change_to << m_index;
    return *this;
}

bool BitProxy:: operator+() const
{

}
bool BitProxy:: operator-() const
{

}
bool BitProxy:: operator&&(bool other) const
{

}
bool BitProxy:: operator||(bool other) const
{

}
bool BitProxy:: operator()()const
{

}

friend std::ostream operator<<(std::ostream os, BitProxy &prox);


#endif// ILRD__RD101_BIT_PROXY_HPP