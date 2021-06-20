/*****************************************************************************
 *	FILENAME:	ex36.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for ex36, ex37 lib.						      	 	 *
 *																			 *
 *****************************************************************************/

#include <iostream> // cout
/*****************************************************************************/
class X;
void Foo(X x);
/*****************************************************************************/
class X
{
public:
	X() { std::cout << "X ctor" << std::endl; }
	//	X(const X &other): m_a(other.m_a) {}
 	virtual ~X() { std::cout << "X dtor" << std::endl; }

private:
	double m_a;
};

class Y: public X
{
public:
	Y() { std::cout << "Y ctor" << std::endl; }
	virtual ~Y() { std::cout << "Y dtor" << std::endl; }

private:
	int m_b;
};
/********************************** driver ***********************************/
int main(void)
{
	Y y1;

	Foo(y1);

	return 0;
}
/*****************************************************************************/
void Foo(X x)
{
	std::cout << "size of x is: " << sizeof(x) << std::endl;
}
/*****************************************************************************/