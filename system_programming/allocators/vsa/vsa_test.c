#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/
#include <unistd.h>

#include "vsa.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
#define SIZE 106

void Test(); 
void Print(vsa_t *pool);

int main()
{
    system("clear");
    
    Test(); 
    
    return 0; 
}

void Test()
{
	vsa_t *vsa = malloc(SIZE);
	char *tmp[3];	
	
    printf(CYAN"\tTest \n\n"WHITE); 
    
	vsa = VsaInit(vsa, SIZE);

	Print(vsa);
	
    TEST(" largest ", 80 , VsaLargestChunkAvailable(vsa)); 
	tmp[0] = VsaAlloc(vsa, 1);
	Print(vsa);
	tmp[1] = VsaAlloc(vsa, 10);
	Print(vsa);
	tmp[2] = VsaAlloc(vsa, 20);
	Print(vsa);


   	VsaFree(tmp[1]);
    TEST(" largest ", 16 , VsaLargestChunkAvailable(vsa)); 
	Print(vsa);
   	VsaFree(tmp[0]);
	Print(vsa);
   	VsaFree(tmp[2]);
	Print(vsa);

	tmp[2] = VsaAlloc(vsa, 40);
	Print(vsa);
    

    printf(CYAN"\tEnd Test \n\n"WHITE); 
    
    free(vsa);
}

void Print(vsa_t *pool)
{
	size_t *vsa = (size_t *)pool;
	printf("%ld\t", *vsa);
	while (*vsa != 0x90909090)
	{
		++vsa;
		printf("%ld\t", *vsa);
	}
	printf("\n");
}
