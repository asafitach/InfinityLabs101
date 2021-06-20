/*****************************************************************************
 *	FILENAME:	ex28.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    testing for ex28 lib.							      	 	 *
 *																			 *
 *****************************************************************************/

#include <iostream> // std
/*****************************************************************************/
static int g_a;
static int g_b = 0;
static int g_c = 1;

class X
{
public:
	X() : m_id(++s_cntr) {}
	int GetId() { std::cout << m_id << std::endl; return m_id; }
	static int GetSpecialId();
private:
	int m_id;
	static int s_cntr;
};

int X::s_cntr = 0;

int X::GetSpecialId()
{ 
	std::cout << s_cntr << std::endl; 
	return (s_cntr * (-1)); 
}

int main()
{
	X x1;
	X x2;
	X x3;

	x1.GetId();
	x2.GetId();
	x1.GetSpecialId();
	X::GetSpecialId();
	

	return 0;
}
/*****************************************************************************/