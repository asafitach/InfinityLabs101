#ifndef __ILRD_RD101_STRING_HPP__
#define __ILRD_RD101_STRING_HPP__

#include <iostream>

namespace ilrd
{
    class String;
}



namespace ilrd
{

    class String
    {
    public:
        String(const char *str = "");
        String(const String& other_); 
        friend std::ostream& operator<<(std::ostream& os, const String &str);
        String&operator=(const String& other_);
        bool operator==(const String& other_);
        bool operator<(const String& other_);
        bool operator>(const String& other_);


        const char *CStr() const;
        size_t Length() const;
        
        ~String();

    private:
        char *m_cstr;
        char *CreateString(const char *str);
};
}

#endif/* ILRD_RD101_STRING_HPP__ */