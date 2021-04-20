#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/
#include "utility.h"

#include "bst.h"

#define SIZE 20

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
void Test(); 

int main()
{
    system("clear");
    
    Test(); 
    
    return 0; 
}

void Test()
{
	int param = 1;
    bst_t *tree = BstCreate(IntCmpFunc, (void *)&param);
    bst_iter_t runner = NULL;
    int *data = NULL;
    int arr[SIZE] = {64,5,4,9,11,3,12,16,22,256,2,33,56,95,44,47,84,61,1,266};
    int index = 0;

   /* GetRandomArray(arr, SIZE, 10);
    */PrintArr(arr, SIZE);
    printf(CYAN"\tTest \n\n"WHITE); 

    TEST(" create ", (tree != NULL) , 1); 

    for (index = 0; index < SIZE/2; ++index)
    {
        runner = BstInsert(tree, (void *) &(arr[index]));
        data = (int *)BstGetData(runner);
        printf("%d ", *data);
        runner = BstInsert(tree, (void *) &(arr[SIZE - index - 1]));
        data = (int *)BstGetData(runner);
        printf("%d ", *data);
    }

  /*  runner = BstBegin(tree);
    */data = (int *)BstGetData(runner);
    printf("%d ", *data);

    for (index = 1; index < SIZE; ++index)
    {
        data = (int *)BstGetData(runner);
        printf("%d", *data);
        runner = BstNext(runner);
    }
    

    TEST("  ", 1 , 1); 
    
    TEST("  ", 1 , 1); 
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 
	BstDestroy(tree);
}

