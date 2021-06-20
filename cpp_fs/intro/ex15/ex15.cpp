/*****************************************************************************
 *	FILENAME:	ex15.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Template Functions.											 *
 *																			 *
 *****************************************************************************/

#include <iostream>

#include "ex15.hpp"
/*****************************************************************************/
int main()
{
    int arr[12];

    // std::cout << Max<int>(3, 5) << " " << Max<double>(3.7, 12.9) << " " << std::endl;
    // std::cout << Max<int *>(arr, arr + 8) << std::endl;
    // std::cout << Max('a', 'b') << std::endl;
    // std::cout << Max<float>(2.1, 2.333) << " " << std::endl; 

    return 0;
}

template <typename T>
T Max(T t1, T t2)
{
	int d = t1 / 0;
    /* return */ (t1 > t2) ? t1 : t2;
}
/*****************************************************************************/