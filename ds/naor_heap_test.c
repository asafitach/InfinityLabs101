#include <stdlib.h>/*malloc free*/
#include <stdio.h>/*printf*/
#include <time.h> /* clock_t, CLOCKS_PER_SEC, clock */
#include <string.h>/*strcmp*/
#include "heap.h"
/*****************************************************************************/
#define RED "\033[5;91m"           /* print in red          */
#define GREEN "\033[1;38;5;47m"    /* print in green        */
#define MAGEN "\033[0;38;5;183m"   /* print in magenta      */
#define YELLOW "\033[1;38;5;220m"  /* print in light yellow */
#define CYAN "\033[0;96m"          /* print in cyan         */
#define LIGHT "\033[2;37m"         /* print in gray         */
#define PURPLE "\033[1;4;38;5;224m"/* print in purple       */
#define RESET "\033[1;0m"          /* reset print color     */
/*****************************************************************************/
#define TEST(name, actual, expected)\
    				printf("%s: %s\n\n", name, actual == expected ?\
     				GREEN"Pass"RESET : RED"Fail"RESET)

#define NOT_TEST(name, actual, expected)\
    				printf("%s: %s\n\n", name, actual != expected ?\
     				GREEN"Pass"RESET : RED"Fail"RESET)	

#define FIND(name, actual, expected)\
    				printf("%s: %s\n\n", name, actual != expected ?\
     				GREEN"FOUND"RESET : RED"NOT FOUND"RESET)	                       
/****************************************************************************/
int cmpfunc (const void * a, const void * b);
int IntIsMatch(const void *data, void *param);
/****************************************************************************/
int main()
{
    int one = 1;
	int two = 2;
	int three = 3;
	int four = 4;
	int five = 5;
	int six = 6;
    int seven = 7;
    int eight = 8;
	int nine = 9;
	int ten = 10;

    int count_insetr_fails = 0;

    void *removed_element = NULL;

    heap_t *heap =  HeapCreate(cmpfunc);

    printf(YELLOW"\n***************Test Heap***************\n\n"RESET);

    NOT_TEST("Test Heap Create", heap, NULL);
    TEST("Test HeapIsEmpty = 1", HeapIsEmpty(heap), 1);
    TEST("Test HeapSize = 0", HeapSize(heap), 0);

    count_insetr_fails += HeapPush(heap, &five);
    count_insetr_fails += HeapPush(heap, &two);
    count_insetr_fails += HeapPush(heap, &six);
    count_insetr_fails += HeapPush(heap, &nine);
    count_insetr_fails += HeapPush(heap, &seven);
    count_insetr_fails += HeapPush(heap, &one);
    count_insetr_fails += HeapPush(heap, &ten);
    count_insetr_fails += HeapPush(heap, &three);
    count_insetr_fails += HeapPush(heap, &four);
    count_insetr_fails += HeapPush(heap, &eight);

    TEST("Test Heap Push 10 elements status", count_insetr_fails, 0);
  
    TEST("Test HeapIsEmpty = 0", HeapIsEmpty(heap), 0);
    TEST("Test HeapSize = 10", HeapSize(heap), 10);
    TEST("Test HeapPeek =  10", HeapPeek(heap), &ten);
    printf(GREEN"Print  elemetns in array\n\n"RESET);
    PrintHeap(heap);
    HeapPop(heap);
    printf(GREEN"Print  elemetns in array after Heap Pop\n\n"RESET);
    PrintHeap(heap);

    TEST("Test HeapPop =  ", HeapSize(heap), 9);

    removed_element = HeapRemove(heap, IntIsMatch, &eight);

    TEST("Test HeapRemove(first elements smaller than 8) = 6  ", removed_element , &six);

    PrintHeap(heap);


    HeapDestroy(heap);

    printf(YELLOW"\n***************END Test Heap***************\n\n"RESET);

    return(0);
}
/****************************************************************************/
int cmpfunc (const void * a, const void * b) 
{
	return ( *(int*)a - *(int*)b );
}
/****************************************************************************/

int IntIsMatch(const void *data, void *param)
{ 
    int int_data = *(int *)data;
    int int_param = *(int *)param;
	return(int_data < int_param);
}