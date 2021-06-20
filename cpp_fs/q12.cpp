#include <iostream>

namespace useless
{
	unsigned int g_wasteful[400];
	extern int g_notthere;
	void Foo() {std::cout<<"foo from useless\n";}

	namespace wasteoftyme
	{	
		void Foo() {std::cout<<"foo from useless::wasteoftyme\n";}
	}//namespace wasteoftyme
}//namespace useless

namespace stupid
{
	void Foo() {std::cout<<"foo from stupid\n";}
	void Bar() {std::cout<<"bar from stupid\n";}
	void DoNothing() {std::cout<<"do nothing from stupid\n";}
}//namespace stupid

namespace useless
{
	void DoNothing(int) {std::cout<<"do nothing from useless\n";}
}//namespace useless

using namespace useless;

void DoStuff()
{
	stupid::Bar();
	Foo();
	using stupid::Foo;
	Foo();
	DoNothing(g_wasteful[3] + 1);
}

void Foo(){std::cout<<"foo from 38 line\n";}

using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
	comeon::Foo();
	::Foo(); //try uncommenting, solve error
	Bar();
	DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
	void DoUselessStuff()
	{
		DoNothing(g_wasteful[3] + 1);
	}
}//namespace useless
int main()
{
	DoStuff();
	DoMoreStuff();


	return 0;
}