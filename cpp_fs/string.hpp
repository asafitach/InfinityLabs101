#ifndef __ILRD_RD101_STRING_HPP__
#define __ILRD_RD101_STRING_HPP__

class string
{
public:
    string();
    string(const char *str);
    string(const string& other_); 
    string&operator=(const string& other_);

    char *CStr();
    size_t Length();
    
    ~string();

private:
    char *m_cstr;
    size_t m_length;
};

#endif/* ILRD_RD101_STRING_HPP__ */