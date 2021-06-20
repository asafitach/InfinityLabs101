/*****************************************************************************
 *	FILENAME:	ex17.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    New types of variables.										 *
 *																			 *
 *****************************************************************************/

#include <iostream>
#include <typeinfo>
/*****************************************************************************/
typedef struct student
{
	int id;
	char *name;
} student_t;

void Foo(const double &dr);
void Bar(double &d);
/*****************************************************************************/
int &ReturnRef(int x)
{
	int &xp = x;
	xp = 3;

	return xp;
} 

void ByRef(int &x)
{
	x = 10;
} 

void Foo(const double &dr)
{
	std::cout << "Foo(const double &dr):" << std::endl;
	std::cout << "address: " << &dr << std::endl;
	std::cout << "value: " << dr << std::endl << std::endl;
}

void Bar(double &d)
{
	std::cout << "Bar(double &d):" << std::endl;
	std::cout << "address: " << &d << std::endl;
	std::cout << "value: " << d << std::endl << std::endl;
}

int main(void)
{
	/* vars */
	int i = 8;
	int &ip = i;
	ip = 9;
	std::cout << "int: " << i << std::endl;
	std::cout << "address of i: " << &i << std::endl; 
	std::cout << "address of ip: " << &ip << std::endl; 
	std::cout << "size of ip: " << sizeof(&ip) << std::endl << std::endl; 

	/* as params */
	int p = 1;
	int &pp = p;
	ByRef(pp);
	std::cout << "as param: " << pp << std::endl;
	std::cout << "address of pp: " << &pp << std::endl; 
	std::cout << "size of ip: " << sizeof(&pp) << std::endl << std::endl; 

	/* by ref */
	int x = 0;
	ByRef(x);
	std::cout << "changed by ref: " << x << std::endl;
	
	/* return val */
	int y = 0;
	int zp = ReturnRef(y);
	std::cout << "return val: " << zp << std::endl; 
	std::cout << "address of zp: " << &zp << std::endl;
	std::cout << "size of zp: " << sizeof(&zp) << std::endl << std::endl;
	
	/* struct fields */
	student_t s = {0};
	s.id = 0;
	s.name = "chiko";
	student_t &sp = s; 
	sp.id = 1;
	sp.name = "ruven";
	std::cout << "struct id: " << s.id << std::endl;
	std::cout << "struct name: " << s.name << std::endl;
	std::cout << "address of s: " << &s << std::endl; 
	std::cout << "address of sp: " << &sp << std::endl;
	std::cout << "size of s: " << sizeof(student_t) << std::endl; 
	std::cout << "size of sp: " << sizeof(&sp) << std::endl << std::endl; 
	
	/* ex18 */
	double d = 2.4;
	Foo(d);
	Bar(d);
	
	int j = 2;
	Foo(j);

	double &jr = reinterpret_cast<double &>(j); 
	Foo(jr);
	std::cout << "was 2 now: " << jr << std::endl;
	std::cout << "was 2 now: " << j << std::endl;

	return 0;
}
/*****************************************************************************/