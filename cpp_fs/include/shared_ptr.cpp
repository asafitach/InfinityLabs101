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

 	Shared_ptr<a> ptr1(new a());
	Shared_ptr<a> ptr11(ptr1);
	Shared_ptr<a> ptra(new b());
	Shared_ptr<b> ptr4(new b());
	Shared_ptr<a> ptr2(reinterpret_cast<Shared_ptr<a>&>(ptr4));
	Shared_ptr<a> ptr3();

    ptr1 = ptr11;
    //ptr3 = ptr1;


    // ptr1->Print(); 
    (*ptra).Print();
    (*ptr4).Print();
//    (*ptr3).Print();
    (*ptr2).Print(); 

    

    //std::cout<<ptr1<<" "<<*ptr1<<std::endl;

std::cout<<"hello\n";


	return 0;
}