// #ifndef ILRD__RD101_BIT_PROXY_HPP
// #define ILRD__RD101_BIT_PROXY_HPP

// #include <iostream>
// #include "bitarray.hpp"

// #define BYTE 8

// class BitProxy
// {
// public:
//     BitProxy& operator=(const BitProxy &other);
//     BitProxy& operator=(bool change_to);

//     bool operator!();
//     // bool operator&&(bool other) const;
//     // bool operator||(bool other) const;
//     bool operator()()const;

//     friend std::ostream& operator<<(std::ostream os, BitProxy &prox);
//     friend class BitArray;

// private:
//     explicit BitProxy(char &array, size_t index);
//     virtual ~BitProxy();
//     char &m_byte_to_refer;
//     char m_index;
// };//BitProxy



// BitProxy::BitProxy(char &array, size_t index): 
//             m_byte_to_refer(array), 
//             m_index(index % BYTE)
// {
// }

// BitProxy::~BitProxy()
// {
// }


// BitProxy &BitProxy::operator=(bool change_to)
// {
//     /*         &   |   ^   
//         0    1 0     0   1   1
//         1    0 1     0   1   1
//         0    1 1     1   1   0
//         1    0 0     0   0   0
//      */
    
//     m_byte_to_refer &= ~(1 << m_index);
//     m_byte_to_refer &= change_to << m_index;
//     return *this;
// }

// bool BitProxy:: operator&&(bool other) const
// {
//     return ((m_byte_to_refer & (1 << m_index)) && other);
// }
// bool BitProxy:: operator||(bool other) const
// {
//     return ((m_byte_to_refer & (1 << m_index)) || other);
// }
// bool BitProxy:: operator()()const
// {
//     return (m_byte_to_refer & (1 << m_index));
// }

// std::ostream& operator<<(std::ostream os, BitProxy &prox)
// {
//     return (os<<(prox.m_byte_to_refer & (1 << prox.m_index)));
// }


// #endif// ILRD__RD101_BIT_PROXY_HPP