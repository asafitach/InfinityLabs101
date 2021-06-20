
#include <iostream>
using namespace std;
/*****************************************************************************/

class X;

int operator+(const X& x1_, const X& x2_)
{
	return 7;
}

ostream& operator<<(ostream& os_, const X& x_);

class X
{
public:
	bool operator==(const X& o_) const { return m_a == o_.m_a; } // java style

private:
	friend ostream& operator<<(ostream& os_, const X& x_);
	int m_a;
};

/* X::X
{m_a = 0; return *this;}
 */

int main(void)
{
	X x1;
	X x2;

	cout<< " x1+x2:" << x1 + x2 <<
		   " x1==x2" << (x1 == x2) <<
		   " x1:" << x1 <<
		   " x2:" << x2 << endl;

	return 0;
}

ostream& operator<<(ostream& os_, const X& x_)
{

}
/*****************************************************************************/