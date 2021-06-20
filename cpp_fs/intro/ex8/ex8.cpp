/*****************************************************************************
 *	FILENAME:	ex8.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    testing for ex8 lib.							      	 	 *
 *																			 *
 *****************************************************************************/

#include <iostream>

/*****************************************************************************/
int main(void)
{
	char *i = "!";
	int j = 0;
	
	std::cout << "Hello World " << i << std::endl;
	std::cerr << "Hi Again " << i << std::endl; 

	std::cin >> j;
	std::cout << "End " << j << std::endl;

	return 0;
}
/*****************************************************************************/