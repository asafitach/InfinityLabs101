/*****************************************************************************
 *	FILENAME:	ex15_2.cpp              AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    testing for ex15_2 lib.							      	 	 *
 *																			 *
 *****************************************************************************/

#include <iostream>

#include "ex15.hpp"
/*****************************************************************************/
void DoSomeThing(void)
{
    int arr[12];

    // std::cout << Max(3, 5) << " " << Max<double>(3.7, 12.9) << " " << std::endl;
    // std::cout << Max<int *>(arr, arr + 8) << std::endl;
    // std::cout << Max('a', 'b') << std::endl;
    // std::cout << Max<float>(2.1, 2.333) << " " << std::endl; 
}

template <typename T>
T Max(T t1, T t2)
{
    (t1 > t2) ? t1 : t2;
}
/*****************************************************************************/