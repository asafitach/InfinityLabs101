/*****************************************************************************
 *	FILENAME:	ex27.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    testing for ex27 lib.							      	 	 *
 *																			 *
 *****************************************************************************/

#include <iostream> // std
/*****************************************************************************/
class X
{
public:
    X();
    X(int a_);
    X(int a_, int b_);

    operator int() const;
    void Print() const;

private:
    int m_a;
};

X::X(): m_a(0){}
X::X(int a_): m_a(a_){}
X::X(int a_, int b_): m_a(a_ + b_){}

X::operator int() const
{
    return m_a;
}

void X::Print() const
{
    std::cout << "X::Print() " << m_a << std::endl;
}

void Fifi(X x_ )
{
    std::cout << "Fifi() " << x_ << std::endl;
    x_.Print();
}

int main()
{
    X x1(7);

    std::cout << sizeof(x1) << std::endl;

    Fifi(x1); //1
    Fifi(X(7)); //2
    Fifi(9); //3
    Fifi(3, 4);

    std::cout << x1 * 3 << std::endl;

    return x1 * 3; //5
}
/*****************************************************************************/