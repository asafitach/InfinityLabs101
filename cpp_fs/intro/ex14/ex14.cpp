/*****************************************************************************
 *	FILENAME:	ex14.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    inline.												      	 *
 *																			 *
 *****************************************************************************/

#include <iostream>

using namespace std;

inline void foo(void);
/*****************************************************************************/
int main(void)
{
	foo();

	return 0;
}
/*****************************************************************************/
inline void foo(void)
{
	cout << "abc";
}
/*****************************************************************************/