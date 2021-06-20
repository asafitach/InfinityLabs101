/*****************************************************************************
 *	FILENAME:	ex23.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    testing for ex23 lib.							      	 	 *
 *																			 *
 *****************************************************************************/

#include <iostream>

using namespace std;
/*****************************************************************************/
struct X
{
    X(int a_, int b_);

    void Inc();
    void Dec();

    int m_a;
    int m_b;
};

X::X(int a_, int b_): m_a(a_), m_b(b_) 
{
    cout << "this is con: " << this << endl;
}

void X::Inc()
{
    ++m_a;
    ++m_b;

	cout << "this: " << this << endl;
}

void X::Dec()
{
    --m_a;
    --m_b;

	cout << "this: " << this << endl;
}

void Inc()
{}
    

int main()
{
	X x1(7, -55); // ctor 
    X x2(x1); // cctor
	cout << "this: " << &x1 << endl;

    Inc();
    x1.Inc();
    x1.Inc();
    x2.Dec();

    return 0;
}
/*****************************************************************************/