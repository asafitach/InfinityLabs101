#include "complex_numbers.hpp"


namespace ilrd
{

using std::ostream; 
using std::istream;


    Complex::Complex(double a, double b): m_real(a), m_img(b)
    {
    }

    Complex& Complex:: operator+(const Complex& other_)
    {
        m_real += other_.m_real;
        m_img += other_.m_img;
    }

    Complex& Complex:: operator-(const Complex& other_)
    {
        m_real -= other_.m_real;
        m_img -= other_.m_img;
    }

    Complex::Complex& operator*(const Complex& other_) 
    {
        double total_a = (m_real * other_.m_real) - (m_img * other_.m_img);
        m_img = (m_real * other_.m_img) + (m_img * other_.m_real);
        m_real = total_a;
    }

    Complex::Complex& operator/(const Complex& other_) const
    {
        double total_real = (m_real / other_.m_real) + (m_img / other_.m_img);
        m_img = (m_img / other_.m_real) - (m_real / other_.m_img);
        m_real = total_real;
    }
    
    bool Complex:: operator==(const Complex& other_) const
    {
        return ((m_real == other_.m_real && m_img == other_.m_img) ? true: false);
    }

    bool Complex:: operator!=(const Complex& other_) const
    {
        return (!(*this == other_));
    }

    void Complex:: SetReal(double a)
    {
        m_real = a;
    }

    void Complex:: SetImaginary(double b)
    {
        m_img = b;
    }

    double Complex::GetReal(void) const
    {
        return (m_real);
    }

    double Complex::GetImaginary(void) const
    {
        return (m_img);
    }

    ostream& operator<<(ostream& os_, const Complex& complex_)
    {
        os_<<"real: "<<complex_.m_real<<" imaginary: "<<complex_.m_img;
    }

    istream& operator>>(istream& is_, const Complex& complex_)
    {
        is_>>"real: ">>complex_.m_real>>" imaginary: ">>complex_.m_img;
    }
    



}