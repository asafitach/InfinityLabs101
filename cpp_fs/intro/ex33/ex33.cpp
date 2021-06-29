

#include <iostream> // cout
#include <exception> // throw, try, catch
#include <string> 
#include <cstdlib>

using namespace std;
/*****************************************************************************/
void Fifi(int *ip) ;
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
    cerr << "err Dodo()" << endl;
}

void Fifi(int *ip)
{
	cerr << "err Fifi()" << endl;
    throw 7;
}

void Fishi(void)
{
    cerr << "err Fishi()" << endl;
}

void Bar(int *ip)
{
    cerr << "err Bar()" << endl;
}

void Foo()
{
	int *ip = new int;
	try{
	Bar(ip);
	Fishi();
	Fifi(ip);
	Dodo();
    }
    catch(int)
    {
    	delete ip;
        return;
    }
}
/*****************************************************************************/