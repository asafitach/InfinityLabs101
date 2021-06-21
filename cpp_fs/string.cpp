#include <iostream>
#include <cstring>
#include <cstdlib>
#include "string.hpp"



String::String()
{
    m_cstr = NULL;

}

String::String(const char *str)
{
    m_length = strlen(str);
    m_cstr = new char[m_length + 1];
    strcpy(m_cstr, str);
}

String::~String()
{
    delete[] m_cstr;
    m_cstr = NULL;
}

 String::String(const String &other_)
{
    m_length = other_.m_length;
    m_cstr = new char[m_length + 1];
    strcpy(m_cstr, other_.m_cstr);
}

String&String::operator=(const String& other_)
{
    m_length = other_.m_length;
    delete[] m_cstr;
    m_cstr = new char [m_length + 1];
    strcpy(m_cstr, other_.m_cstr);

    return (*this);
}

bool String::operator==(const String& other_)
{
    return (strcmp(m_cstr, other_.m_cstr));
}


bool String::operator<(const String& other_)
{
    return ((0 > strcmp(m_cstr, other_.m_cstr)) ? true: false);
}

bool String::operator>(const String& other_)
{
    return ((0 < strcmp(m_cstr, other_.m_cstr)) ? true: false);
}

char *String::CStr()
{
    return m_cstr;
}

size_t String::Length()
{
    return m_length;
}

std::ostream& operator<<(std::ostream& os, const String &str)
{
    return (os<<str.m_cstr);
}

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

    return (0);
}

