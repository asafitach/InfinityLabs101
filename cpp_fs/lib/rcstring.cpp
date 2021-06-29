#include <cstring>
#include <cstdlib>
#include "rcstring.hpp"

#define ASSERT(cond) int sizeof_char_assert[(cond) ? 1 : -1]
ASSERT(sizeof(char) == 1);
/*****************************************************************************/
namespace ilrd
{
/*****************************************************************************/
/*************************  o p e r a t o r s ********************************/
std::ostream& operator<<(std::ostream& os_, const RCString& str)
{
    return (os_<<str.CStr());
}
/*****************************************************************************/

bool operator==(const RCString& left, const RCString& right)
{
    return (left.CStr() == right);
}
/*****************************************************************************/

bool operator==(const char *left, const RCString& right)
{
    return (!strcmp(left, right.CStr()));
}
/*****************************************************************************/

bool operator==(const RCString& left, const char *right)
{
    return (right == left);
}
/*****************************************************************************/

bool operator<(const RCString& left, const RCString& right)
{
    return (strcmp(left.CStr(), right.CStr()));
}
/*****************************************************************************/

bool operator>(const RCString& left, const RCString& right)
{
    return (right < left);
}
/*****************************************************************************/

/*****************************************************************************/
/*************************  c o n s t r u c t o r ****************************/

RCString::StrRef *RCString::InitStr(const char *str)
{
    size_t len = strlen(str) + 1;
    size_t offset = offsetof(StrRef, str);
    StrRef *tmp = static_cast<StrRef *>(operator new((len * sizeof(char)) + offset));
    memcpy(tmp->str, str, len);
    tmp->counter = 1;
    return (tmp);
}
/*****************************************************************************/

RCString::RCString(const char *str) throw(std::bad_alloc):m_strRef(InitStr(str))
{
}
/*****************************************************************************/

/*****************************************************************************/
/************************  r u l e   o f   t h r e e  ************************/

RCString::RCString(const RCString& other): m_strRef(other.m_strRef)
{
    ++m_strRef->counter;
}
/*****************************************************************************/
void RCString::DtorHelper()
{
    if (1 < m_strRef->counter)
    {
        --m_strRef->counter;
    }
    else
    {
        operator delete (m_strRef);
        m_strRef = NULL;
    }
}

RCString::~RCString()
{
    DtorHelper();
}
/*****************************************************************************/

RCString&RCString:: operator=(const RCString& other)
{
    DtorHelper();

    m_strRef = other.m_strRef;
    ++m_strRef->counter;

    return (*this);
}
/*****************************************************************************/

/*****************************************************************************/
/******************  m e m b e r   f u n c t i o n s *************************/
char& RCString:: operator[](const size_t index)throw(std::bad_alloc)
{
    if (1 < m_strRef->counter)
    {
        --m_strRef->counter;
        m_strRef = InitStr(m_strRef->str);
    }
        return(m_strRef->str[index]);
}
/*****************************************************************************/

char RCString::operator[](const size_t index) const
{
    return(m_strRef->str[index]);
}
/*****************************************************************************/

size_t RCString:: Length() const 
{
    return (strlen(m_strRef->str));
}
/*****************************************************************************/

const char *RCString::CStr() const
{
    return (m_strRef->str);
}
/*****************************************************************************/   

}//namespace ilrd

