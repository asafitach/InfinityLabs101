/*****************************************************************************
 *	FILENAME:	ex16.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    testing for ex16 lib.							      	 	*
 *																			 *
 *****************************************************************************/

#include <iostream>
#include <typeinfo>
/*****************************************************************************/
template <typename T>
void foo(T t)
{
    std::cout << t << " Generic foo for " << typeid(t).name() << std::endl;
}

template <>
void foo<int>(int t)
{
    std::cout << t << " Specialized foo (for int param)\n";
}

int main(void)
{
    // foo(4.2);
    // foo(5);
    // foo<int>(5);

    return 0;
}
/*****************************************************************************/