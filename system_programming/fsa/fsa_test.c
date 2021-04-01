#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/

#include "fsa.h"

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
	fsa_t *fsa = NULL;
	size_t suggest = FsaSuggestedSize(9, 15);
	size_t index = 0;
	void *ptr = NULL;
	
    printf(CYAN"\tTest \n\n"WHITE); 
    
    TEST("suggest size ", suggest , 272); 
    
    fsa = malloc(suggest);
    if (NULL == fsa)
    {
    	printf("Aloocation failed\n");
    }
    
    fsa = FsaInit(fsa, suggest, 9);
    
    TEST("init + count free ", FsaCountFreeBlocks(fsa) , 15); 
    
    for (index = 0; index < 10; index++)
    {
    	ptr = FsaAllocBlock(fsa);
    	*(size_t *)&ptr = (size_t)(10 * index); 
    }
    
    FsaAllocBlock(fsa);
    TEST("alloc  ", FsaCountFreeBlocks(fsa) , 4); 
    
    FsaFreeBlock(fsa, &ptr);
    
    TEST("free  ", FsaCountFreeBlocks(fsa) , 5); 
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 
    free(fsa);
}
