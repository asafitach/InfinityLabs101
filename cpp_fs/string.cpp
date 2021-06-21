#include <iostream>
#include <cstring>
#include <cstdlib>
//#include "string.cpp"

class string
{
public:
    string();
    string(const char *str);
    string(const string& other_); 
    string&operator=(const string& other_);

    ~string();
    
    char *CStr();
    size_t Length();

private:
    char *m_cstr;
    size_t length;
};

string::string()
{
    m_cstr = NULL;

}

string::string(const char *str)
{
    length = strlen(str);
    m_cstr = new char[length + 1];
    strcpy(m_cstr, str);
    m_cstr[length] = '\0';
}

string::~string()
{
    delete[] m_cstr;
    m_cstr = NULL;
}

 string::string(const string &other_)
{
    length = strlen(other_.m_cstr);
    m_cstr = new char[length + 1];
    strcpy(m_cstr, other_.m_cstr);
    m_cstr[length] = '\0';
}

string&string::operator=(const string& other_)
{
    length = strlen(other_.m_cstr);
    delete[] m_cstr;
    m_cstr = new char [length + 1];
    strcpy(m_cstr, other_.m_cstr);
    m_cstr[length] = '\0';

    return (*this);
}

char *string::CStr()
{
    return m_cstr;
}

size_t string::Length()
{
    return length;
}

int main()
{
    string c1("hello");
    string c2(" world!");
    string c3;
    c3 = c2;

    std::cout<<c1.CStr()<<" ";
    std::cout<<c1.Length()<<std::endl;

    std::cout<<c2.CStr()<<" ";
    std::cout<<c2.Length()<<std::endl;

    std::cout<<c3.CStr()<<" ";
    std::cout<<c3.Length()<<std::endl;

    return (0);
}

