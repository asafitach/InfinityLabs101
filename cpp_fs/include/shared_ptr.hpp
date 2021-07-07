#ifndef __ILRD__RD101_SHARED_PTR_HPP
#define __ILRD__RD101_SHARED_PTR_HPP

#include <iostream>


template <typename T>
class Shared_ptr
{
public:
	template <typename S_P_T>
    friend class Shared_ptr<T>;
	
	explicit Shared_ptr(T* ptr = NULL);
	Shared_ptr(Shared_ptr& other);
    Shared_ptr& operator=(Shared_ptr<T> &other);
	virtual ~Shared_ptr();
	
	template <typename S_P_T>
	Shared_ptr(Shared_ptr<S_P_T>& other);
	template <typename S_P_T>
    Shared_ptr& operator=(Shared_ptr<S_P_T> &other);

	T* getAddress()const;
	T& operator*()const;
	T* operator->()const;
    operator T*()const;
    void dtorHelper();

private:
	size_t* m_counter;
	T* m_ptr;
};//Shared_ptr




template <typename T> Shared_ptr <T>:: Shared_ptr(T* ptr)
								:m_counter(new size_t(0)), m_ptr (ptr) 
{
	(*m_counter)++;
    std::cout<<"ctor "<<*m_counter<<" "<<m_ptr<<std::endl;
}


template <typename T>	Shared_ptr<T>:: Shared_ptr(Shared_ptr<T>& other): 
								m_counter(other.m_counter), m_ptr(other.m_ptr)
{
	(*m_counter)++;
    std::cout<<"cctor "<<*m_counter<<" "<<m_ptr<<std::endl;
}

template <typename T>	T* Shared_ptr<T>:: getAddress()const
{
    return m_ptr;
}

template <typename T>	T& Shared_ptr<T>:: operator*()const
{
    return *m_ptr;
}

template <typename T>	T* Shared_ptr<T>:: operator->()const
{
    return m_ptr;
}

     
template <typename T>   Shared_ptr<T>:: operator T*()const 
{
    return (m_ptr);
}

template <typename T>   Shared_ptr<T>& Shared_ptr<T>:: operator=(Shared_ptr<T>& other)
{
    (*(other.m_counter))++;
    dtorHelper();
    m_ptr = other.m_ptr;
    m_counter = other.m_counter;
    std::cout<<"=operator "<<*m_counter<<" "<<m_ptr<<std::endl;
    return (*this);
}

template <typename T> void Shared_ptr<T>:: dtorHelper()
{
    std::cout<<"dtor "<<*m_counter<<" "<<m_ptr<<std::endl;
	(*m_counter)--;
	if (0 == *m_counter)
	{
		delete m_counter;
		delete m_ptr;
	}
}

template <typename T> 
Shared_ptr<T>:: ~Shared_ptr()
{
    dtorHelper();
}

template <typename T> 
std::ostream& operator<<(std::ostream& os,Shared_ptr<T>& s_ptr)
{
	return os << s_ptr.m_ptr;
}

template <typename T>
template <typename S_P_T>
Shared_ptr<T>& Shared_ptr<T>:: operator=(Shared_ptr<S_P_T>& other)
{
    (*(other.m_counter))++;
    dtorHelper();
    m_ptr = other.m_ptr;
    m_counter = other.m_counter;
    std::cout<<"=operator "<<*m_counter<<" "<<m_ptr<<std::endl;
    return (*this);
}


template <typename T>	
template <typename S_P_T>   
Shared_ptr<T>:: Shared_ptr(Shared_ptr<S_P_T>& other): 
								m_counter(other.m_counter), m_ptr(other.m_ptr)
{
	(*m_counter)++;
    std::cout<<"cctor "<<*m_counter<<" "<<m_ptr<<std::endl;
}



#endif //__ILRD__RD101_SHARED_PTR_HPP