/*****************************************************************************
 *	FILENAME:	ex12.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    namespace.										      	 	 *
 *																			 *
 *****************************************************************************/

/*****************************************************************************/
namespace useless
{
    unsigned int g_wasteful[400];
    extern int g_nothere;
    void Foo() {}

	namespace wasteoftyme
	{
		void Foo(){}

	}//namespace wasteoftime

}//namespace useless
/*****************************************************************************/
namespace stupid
{
    void Foo(){}
    void Bar(){}
    void DoNothing(unsigned int){}
}//namespace stupid
/*****************************************************************************/
namespace useless
{
    void DoNothing(int) {}
} //namespace useless

using namespace useless;

void DoStuff()
{
    stupid::Bar();
    Foo();
    using stupid::Foo;
    Foo();
    DoNothing(g_wasteful[3] + 1);
}
void Foo() {}

using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
    comeon::Foo();
    wasteoftyme::Foo(); //try uncommenting this line, solve the error
    Bar(); //why doesnt this line create an error
    DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
    void DoUselessStuff()
    {
        DoNothing(g_wasteful[3] + 1);
    }
} //namespace useless
/*****************************************************************************/
int main(void)
{
	
}	
/*****************************************************************************/