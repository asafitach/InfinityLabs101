#ifndef __ILRD_RD101_STRING_HPP__
#define __ILRD_RD101_STRING_HPP__

#include <iostream>

class String;

std::ostream& operator<<(std::ostream& os, const String &str);

class String
{
public:
    String();
    String(const char *str);
    String(const String& other_); 
    friend std::ostream& operator<<(std::ostream& os, const String &str);
    String&operator=(const String& other_);
    bool operator==(const String& other_);
    bool operator<(const String& other_);
    bool operator>(const String& other_);


    char *CStr();
    size_t Length();
    
    ~String();

private:
    char *m_cstr;
    size_t m_length;
};

#endif/* ILRD_RD101_STRING_HPP__ */