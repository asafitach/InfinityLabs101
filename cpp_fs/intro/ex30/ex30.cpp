/*****************************************************************************
 *	FILENAME:	ex30.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    testing for ex30 lib.							      	 	 *
 *																			 *
 *****************************************************************************/

#include <iostream> // std
#include <exception> // throw, try, catch
#include <string> 
#include <cstdlib>
/*****************************************************************************/
using namespace std;

class X
{
    public:
        X():m_a(0){ std::cout << "B::Ctor" << std:: endl; }
        ~X(){ std::cout << "B::Dtor" << std::endl; }
    private:
        int m_a;
};

struct BadDog: public runtime_error
{
    BadDog(const string& s = "This is bad dog"): runtime_error(s) {}
};

void Fifi()
{
	X x2;
    throw BadDog("bad pup"); cerr << "Fifi() after throw" << endl;
}

void Foo()
{
	X x1;
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}

int main() 
{
    try
    {
        Bar();
    }
    catch(bad_alloc&)
    {
        cerr << "Out of memory! exiting."; exit(2);
    }
    catch(BadDog& b)
    {
        cerr << "Bad Dog exception: " << b.what(); exit(3);
    }
    catch(exception& r)
    {
        cerr << "unknown exception:" << r.what();
        exit(4);
    }

    return 0;
}
/*****************************************************************************/