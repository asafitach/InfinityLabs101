
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
struct GoodDog: public runtime_error
{
    GoodDog(const string& s = "This is good dog"): runtime_error(s) {}
};

void Fifi()
{
	X x2;
    throw GoodDog("good pup"); cerr << "Fifi() after throw" << endl;
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
    catch(BadDog& b)
    {
        cerr << "Bad Dog exception: " << b.what(); exit(3);
    }
    catch(bad_alloc&)
    {
        cerr << "Out of memory! exiting."; exit(2);
    }
    catch(exception& r)
    {
        cerr << "unknown exception:" << r.what();
        exit(4);
    }
    catch(GoodDog& b)
    {
        cerr << "Good Dog exception: " << b.what(); exit(3);
    }

    return 0;
}
/*****************************************************************************/