/*****************************************************************************
 *	FILENAME:	ex34.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for ex34 lib.							      	 	 *
 *																			 *
 *****************************************************************************/

// set_unexpected example
#include <iostream>       // std::cerr
#include <exception>      // std::set_unexpected
#include <cstdlib> 
#include <typeinfo>
/*****************************************************************************/
int Foo(int) throw(std::bad_cast)
{
  std::cout << "Foo" << std::endl;
  std::bad_cast cat;
  throw(cat);
  return 0;
}

class X
{
public:
    X(): m_a(0){}
    ~X()
    {
        std::cerr<< "X::Dtor\n" << std::endl;
        std::cerr<< Foo(m_a) << std::endl;
        std::cerr<< "X::Dtor 2\n" << std::endl;
    }
private:
  int m_a;
};

void Bar(void) throw(std::bad_alloc)
{
    std::cout << "Bar" << std::endl;


    //X x2;

      //std::bad_alloc bad;
      //throw(bad);
}

void Fishi()
{
    std::cout << "Fishi" << std::endl;
    
	X x1;
    
	try
    {
	
	}
    catch(const std::bad_alloc & e)
    {
        std::cerr << "bad_alloc catched\n" <<e.what() << '\n';
    }
    catch(const std::bad_cast & e)
    {
        std::cerr << "bad_cast catched" <<e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "main error ";
    }
}//Dtor invoked here thus we cant catch him

int main()
{
  Fishi();
  return 0;
}
/*****************************************************************************/