
#include <iostream> // std
/*****************************************************************************/
// static int g_a;
// static int g_b = 0;
// static int g_c = 1;
class X;
int X::s_cntr = 5;
class X
{
public:
	X() : m_id(++s_cntr) {}
	int GetId() { std::cout << m_id << std::endl; return m_id; }
	void Print_static_location(){std::cout << &m_id<<" "<< &s_cntr << std::endl; return;}
	//static int GetSpecialId();
private:
	int m_id;
	static int s_cntr;
};


/* int X::GetSpecialId()
{ 
	std::cout << s_cntr << std::endl; 
	return (s_cntr * (-1)); 
} */

int main()
{
	X x1;
	X x2;
	X x3;

	x1.GetId();
	x1.Print_static_location();
	x2.GetId();
	x2.Print_static_location();
	//x1.GetSpecialId();
	

	return 0;
}
/*****************************************************************************/