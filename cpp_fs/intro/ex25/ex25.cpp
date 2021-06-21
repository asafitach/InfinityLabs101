
#include <cstdio>
/*****************************************************************************/
class X
{
public:
    explicit X(int a_);
    void Foo();
    friend int printf();
	//friend void Foo(const X &x_);
    void Print();

private:
    int m_a;
};

X::X(int a_)
    : m_a(a_)
    {}

void X::Foo()
{
    printf("%d\n", m_a);
}

/* void Foo(const X &x_)
{
    printf("%d\n", x_.m_a);
}
 */
void X::Print()
{
    printf("%d\n", this->m_a);
}

int main()
{
    X x1(2);
    x1.Print();
    //x1.Foo();
 //   Foo(x1);

    return 0;
}
/*****************************************************************************/