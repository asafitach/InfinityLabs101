
#include <iostream> // std::cerr
#include <cstdlib>	// exit
#include <exception> // std::set_unexpected

using namespace std;

/*****************************************************************************/
void MyUnexpected(void) throw(char) 
{
	std::cerr << "unexpected called\n";
	throw 'a';     // throws int (in exception-specification)
}

void MyTerminate(void) throw(int)
{
	std::cerr << "teminated called\n";
	exit(1);
}

void MyFunction(void) throw(int) 
{	
	throw 'x';   // throws char (not in exception-specification)
}

int main (void) 
{
  std::set_unexpected (MyUnexpected);
  std::set_terminate (MyTerminate);

  try 
  {
    MyFunction();
  }

  catch (int) { std::cerr << "caught int\n"; }
  catch (...) { std::cerr << "caught some other exception type\n"; }
  return 0;
}
/*****************************************************************************/