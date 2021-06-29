#ifndef ILRD_101_RCSTRING_H
#define ILRD_101_RCSTRING_H

#include <cstddef>  /* size_t */
#include <iostream> /* ostream */
#include <typeinfo> // type
#include <stdexcept>

 
namespace ilrd
{
class RCString; 

std::ostream& operator<<(std::ostream& os_, const RCString& str);
bool operator==(const RCString& left, const RCString& right);
bool operator==(const char *left, const RCString& right);
bool operator==(const RCString& left, const char *right);
bool operator<(const RCString& left, const RCString& right);
bool operator>(const RCString& left, const RCString& right);

class RCString 
{
public:
    RCString(const char *str = "") throw(std::bad_alloc);
    RCString(const RCString& other);
    ~RCString();
    
    RCString& operator=(const RCString& other);

    char& operator[](const size_t index) throw(std::bad_alloc);
    char operator[](const size_t index) const; 

    size_t Length() const; 
    const char *CStr() const;
    
private:
    
    struct StrRef
    {
        size_t counter;
        char str[1];
    };

    StrRef *m_strRef;
    StrRef *InitStr(const char *str);
    void DtorHelper();
};

}

#endif /* ILRD_101_RCSTRING_H */