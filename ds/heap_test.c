#include <stdio.h> /*printf*/
#include "heap.h"

/*********************** color macros for printf *********************************/

#define RED "\033[5;91m"           /* print in red          */
#define GREEN "\033[1;38;5;47m"    /* print in green        */
#define MAGEN "\033[0;38;5;183m"   /* print in magenta      */
#define YELLOW "\033[1;38;5;220m"  /* print in light yellow */
#define CYAN "\033[0;96m"          /* print in cyan         */
#define LIGHT "\033[2;37m"         /* print in gray         */
#define PURPLE "\033[1;4;38;5;224m"/* print in purple       */
#define RESET "\033[1;0m"          /* reset print color     */
#define WHITE "\033[0m"


/*****************************************************************************/

#define TEST_IS_EQUAL(test_name, expected, real)\
			(real == expected ?\
			printf("%s:" GREEN" PASS\n"WHITE, test_name) :\
			printf("%s:"  RED" FAIL\n"WHITE, test_name))

#define TEST_IS_TRUE(test_name, result)\
			(result ?\
			printf("%s:" GREEN" PASS\n"WHITE, test_name) :\
			printf("%s:"  RED" FAIL\n"WHITE, test_name))

#define TEST_IS_FALSE(test_name, result)\
			(!result ?\
			printf("%s:" GREEN" PASS\n"WHITE, test_name) :\
			printf("%s:"  RED" FAIL\n"WHITE, test_name))

#define TEST_IS_GREATER_ZERO(test_name, result)\
			(return > 0 ?\
			printf("%s:" GREEN" PASS\n"WHITE, test_name) :\
			printf("%s:"  RED" FAIL\n"WHITE, test_name))		
     				
/********************************* others: ******************************/

int CmpInt(const void *new_data, const void *curr_data);
int IntIsMatch(const void *data1, void *data2);

void TestCreateDestroy();
void TestPush();
void TestSize();
void TestIsEmpty();
void TestPopPeek();
void TestRemove();



int main ()
{
    TestCreateDestroy();
/*    TestPush();
  */  TestSize();
    TestIsEmpty();
 /*   TestPopPeek();
    TestRemove();
   */ return 0;
}

void TestCreateDestroy()
{
    heap_t *heap = HeapCreate(CmpInt);
    HeapDestroy(heap);
}

void TestPush()
{
    heap_t *heap = HeapCreate(CmpInt);
    size_t i = 0;

    for (i = 0; i <= 20; i++)
    {
       HeapPush(heap, (void *) i);
    }
    TEST_IS_EQUAL("TestPush", HeapPeek(heap), (void *)20);
    PrintHeap(heap);
    
    HeapDestroy(heap);
}

void TestIsEmpty()
{
    heap_t *heap = HeapCreate(CmpInt);

    TEST_IS_TRUE("TestIsEmpty", HeapIsEmpty(heap));
    HeapPush(heap, (void *) 8);
    TEST_IS_FALSE("TestIsEmpty", HeapIsEmpty(heap));
    HeapDestroy(heap);
}

void TestPopPeek()
{
    heap_t *heap = HeapCreate(CmpInt);
    size_t i = 0;

    for (i = 0; i <= 8; i++)
    {
       HeapPush(heap, (void *) i);
    }
       
   for (i = 8; i > 0; i--)
    {
        HeapPop(heap);
        TEST_IS_EQUAL("HeapPop",  HeapPeek(heap),(void *) (i-1));
    }

    HeapDestroy(heap);
}

void TestRemove()
{
    heap_t *heap = HeapCreate(CmpInt);
    size_t i = 0;

    for (i = 0; i <= 8; i++)
    {
       HeapPush(heap, (void *) i);
    }

    HeapRemove(heap, IntIsMatch, (void *) 3);

    PrintHeap(heap);

    HeapDestroy(heap);
}

void TestSize()
{
    heap_t *heap = HeapCreate(CmpInt);

    TEST_IS_EQUAL("TestSize", HeapSize(heap), 0);
    HeapPush(heap, (void *) 7);
    HeapPush(heap, (void *) 5);
    HeapPush(heap, (void *) 8);
    TEST_IS_EQUAL("TestSize", HeapSize(heap), 3);

    HeapDestroy(heap);
}
int CmpInt(const void *new_data, const void *curr_data)
{
    return ((*(int **)&new_data) - (*(int **)&curr_data));
}

int IntIsMatch(const void *data1, void *data2)
{
    return (*(int**)&(data1) == *(int**)&(data2));
}

