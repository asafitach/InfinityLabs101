#ifndef ILRD__RD101_BIT_ARRAY_HPP
#define ILRD__RD101_BIT_ARRAY_HPP

#include <string>
#include <stdio.h>

namespace ilrd
{

static const size_t WORD_SIZE  = sizeof(size_t);
static const size_t BITS_IN_BYTE = 8;
static const size_t LUT_SIZE = 256;

template <size_t SIZE = WORD_SIZE>
class BitArray
{
private:
    class BitProxy;
public:
    explicit BitArray();
   
    BitProxy& operator[](size_t index);/* can throw exception "out_of_range" */
    bool operator[](size_t index) const;/* can throw exception "out_of_range" */
    
    bool operator==(const BitArray &other) const;
    bool operator!=(const BitArray &other) const;


    BitArray& operator &=(const BitArray &other);
    BitArray& operator ^=(const BitArray &other);
    BitArray& operator |=(const BitArray &other);

    BitArray& operator <<=(size_t n_times);
    BitArray& operator >>=(size_t n_times);

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
    class Lut
    {
    public:
        Lut();
        size_t GetBitsOn(size_t num);
    private:
        char lut[LUT_SIZE];

    };
    size_t m_array[((SIZE - 1) / (BITS_IN_BYTE * WORD_SIZE)) + 1];
    static Lut m_lut;

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


}
#endif// ILRD__RD101_BIT_ARRAY_HPP
