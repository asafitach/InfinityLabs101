#ifndef ILRD_101_COMPLEX_NUMBERS_H
#define ILRD_101_COMPLEX_NUMBERS_H

#include <iostream>

namespace ilrd
{

class Complex;

inline std::ostream& operator<<(std::ostream& os, const Complex& complex);
inline std::istream& operator>>(std::istream& is, Complex& complex);
inline const Complex operator+(const Complex& left, const Complex& right);
inline const Complex operator-(const Complex& left, const Complex& right);
inline const Complex operator*(const Complex& left, const Complex& right);
inline const Complex operator/(const Complex& left, const Complex& right);
inline bool operator==(const Complex& left, const Complex& right);
inline bool operator!=(const Complex& left, const Complex& right);

// Complex numbers: a + bi 

class Complex  
{
public:
    inline Complex(double a = 0, double b = 0); // for implicit conversions

    inline Complex& operator+=(const Complex& other);
    inline Complex& operator-=(const Complex& other);
    inline Complex& operator*=(const Complex& other);
    inline Complex& operator/=(const Complex& other);
    inline void SetReal(double a);
    inline void SetImaginary(double b);
    inline double GetReal(void) const;
    inline double GetImaginary(void) const;

private: 
    double m_real; // real
    double m_img; // imaginary
};

//in class definitions

inline Complex::Complex(double a, double b): m_real(a), m_img(b)
{
    int i = 0;
    for (i = 3; i < 0xfffff; ++i)
    {
        i *=2;
        i -= 1;
        if (0 == i)
        {
            break;
        }
    }
    std::cout<<i;
} 

inline Complex& Complex:: operator+=(const Complex& other)
{
    m_real += other.m_real;
    m_img += other.m_img;
    return *this;
}

inline Complex& Complex:: operator-=(const Complex& other)
{
    m_real -= other.m_real;
    m_img -= other.m_img;
    return *this;
}

inline Complex& Complex::operator*=(const Complex& other)
{
    double tmp_real = (m_real * other.m_real) - (m_img * other.m_img);
    m_img = (m_real * other.m_img) + (m_img * other.m_real);
    m_real = tmp_real;
    return *this;
}

inline Complex& Complex::operator/=(const Complex& other)
{
    double denominator = other.m_real * other.m_real + other.m_img * other.m_img;
    double temp_m_real = (m_real * other.m_real + m_img * other.m_img) / denominator;
    m_img = (m_img * other.m_real - m_real * other.m_img) / denominator;
    m_real = temp_m_real;
    return (*this);
}

inline void Complex::SetReal(double a)
{
    m_real = a;
}

inline void Complex::SetImaginary(double b)
{
    m_img = b;
}

inline double Complex::GetReal(void) const
{
    return (m_real);
}

inline double Complex::GetImaginary(void) const
{
    return (m_img);
}


inline std::ostream& operator<<(std::ostream& os, const Complex& complex)
{
    return (os<<(complex).GetReal()<<" + "<<(complex).GetImaginary()<<"i");
}

inline std::istream& operator>>(std::istream& is, Complex& complex)
{
    double tmp = 0;
    is>>tmp;
    (complex).SetReal(tmp);

    is>>tmp;
    (complex).SetImaginary(tmp);

    return (is);
}

inline const Complex operator+(const Complex& left, const Complex& right)
{
    Complex tmp(left);
    tmp += right;
    return (tmp);
}

inline const Complex operator-(const Complex& left, const Complex& right)
{
    Complex tmp(left);
    tmp -= right;
    return (tmp);
}

inline const Complex operator*(const Complex& left, const Complex& right)
{
    Complex tmp(left);
    tmp *= right;
    return (tmp);
}

inline const Complex operator/(const Complex& left, const Complex& right)
{
    Complex tmp(left);
    tmp /= right;
    return (tmp);
}


inline bool operator==(const Complex& left, const Complex& right)
{
    return (((left).GetReal() == (right).GetReal() && (left).GetImaginary() == (right).GetImaginary()) ? true: false);
}

inline bool operator!=(const Complex& left, const Complex& right)
{
    return (!(left == right));
}

}//namespace ilrd

#endif /* ILRD_101_COMPLEX_NUMBERS_H */
