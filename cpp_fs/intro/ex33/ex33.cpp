/*****************************************************************************
 *	FILENAME:	ex33.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for ex33 lib.							      	 	 *
 *																			 *
 *****************************************************************************/

#include <iostream> // cout
#include <exception> // throw, try, catch
#include <string> 
#include <cstdlib>

using namespace std;
/*****************************************************************************/
void Fifi(int *ip) throw(int);
void Fishi(void);
void Bar(int *ip);
void Foo();
void Dodo(void);
/********************************* driver ************************************/
int main() 
{
    try
    {
        Foo();
    }
    catch(int)
    {
        cerr << "int exception caught" << endl; 
		exit(2);
    }
    catch(...)
    {
        cerr << "unknown exception caught" << endl;
		exit(4);
    }

    return 0;
}
/*****************************************************************************/
void Dodo(void)
{
    cerr << "Dodo()" << endl;
}

void Fifi(int *ip) throw(int)
{
	cerr << "Fifi()" << endl;
    throw 7;
}

void Fishi(void)
{
    cerr << "Fishi()" << endl;
}

void Bar(int *ip)
{
    cerr << "Bar()" << endl;
}

void Foo()
{
	int *ip = new int;
	
	Bar(ip);
	Fishi();
	Fifi(ip);
	Dodo();

	delete ip;
}
/*****************************************************************************/