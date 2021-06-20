#include <iostream>
#include <typeinfo>
using namespace std;

template<typename T>
void foo(T t)
{
	cout<< t << " Generic foo for " << typeid(t).name() << endl;
}

template<>
void foo (int t)
{
	cout << t << " Specialized foo (for int param) \n";
}

int main()
{
	foo(4.2);
	foo(5);
	foo<int>(5);
	
	return (0);
}



