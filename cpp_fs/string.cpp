#include <iostream>
#include <cstring>
#include <cstdlib>
#include "string.hpp"


char *CreateString(const char *str)
{
    char *cstr = new char[strlen(str) + 1];
    strcpy(cstr, str);

    return (cstr);
}

namespace ilrd
{

String::String(const char *str):m_cstr(CreateString(str))
{
}

String::~String()
{
    delete[] m_cstr;
    m_cstr = NULL;
}

 String::String(const String &other_)
{
    m_cstr = CreateString(other_.m_cstr);
    // String(other_.m_cstr);
}

String&String::operator=(const String& other_)
{
    String tmp(other_);
    delete[] m_cstr;
    m_cstr = CreateString(tmp.m_cstr);

    return (*this);
}

bool String::operator==(const String& other_)
{
    return (!strcmp(m_cstr, other_.m_cstr));
}


bool String::operator<(const String& other_)
{
    return ((0 > strcmp(m_cstr, other_.m_cstr)) ? true: false);
}

bool String::operator>(const String& other_)
{
    return (*this < other_);
}

const char *String::CStr() const
{
    return m_cstr;
}

size_t String::Length() const
{
    return (strlen(m_cstr));
}

std::ostream& operator<<(std::ostream& os, const String &str)
{
    return (os<<str.m_cstr);
}

}