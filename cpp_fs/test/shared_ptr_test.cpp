#include <iostream>
#include <cstdlib>
#include "shared_ptr.hpp"

class a
{
    public:
    explicit a(): m_a(0)
    {}
    explicit a(a& other): m_a(other.m_a)
    {}
    virtual ~a()
    {
    }

    virtual void Print()
    {
        std::cout<<"class a\n";
    }
    private:
    int m_a;
};

class b : public a
{
    public:
    explicit b(): m_b(0)
    {}
    explicit b(b& other): a(other), m_b(other.m_b)
    {}
    virtual ~b()
    {
    }
    void Print()
    {
        std::cout<<"class b\n";
    }
    private:
    int m_b;
};


int main()
{
	ilrd::Shared_ptr<b> ptr4(new b());
 	ilrd::Shared_ptr<a> ptr1(new a());
	ilrd::Shared_ptr<a> ptr11(ptr1);
	ilrd::Shared_ptr<a> ptra(new b());
	ilrd::Shared_ptr<a> ptr2(ptr4);
	ilrd::Shared_ptr<a> ptr3(ptr2);

    ptr1 = ptr11;
    ptr3 = ptr1;


    ptr1->Print(); 
    (*ptra).Print();
    (*ptr4).Print();
    (*ptr3).Print();
    ptr2->Print(); 


	return 0;
}