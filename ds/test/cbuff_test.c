#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/

#include "cbuff.h"

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
	cbuff_t *cbuff = NULL;
	void *data = NULL;
	ssize_t res = 0;
	char str[] = "hello";
	char *str2 = "world";
	int count = 0;
	
    printf(CYAN"\tTest \n\n"WHITE); 
    
	cbuff = CbuffCreate(8);
	
    TEST(" create ", (cbuff != NULL) , 1); 

    count = CbuffIsEmpty(cbuff);
    
    TEST(" is empty ", count , 1); 
    
    count = 0;
        
    res = CbuffRead(cbuff, data, 2);
    
    TEST(" read empty ", res , 0); 
    
    res = CbuffWrite(cbuff, str, 5);
    
    TEST(" write ", res , 5); 

    res = CbuffWrite(cbuff, str2, 5);
    
    TEST(" write to full ", res , 3); 
    
    count = CbuffIsEmpty(cbuff);
    
    TEST(" is empty ", count , 0); 
    
    res = CbuffRead(cbuff, str, 6);
      
    TEST(" read ", res , 6);
 
    res = CbuffCountFull(cbuff);
    
    TEST(" count full ", res , 2); 

    res = CbuffFreeSpace(cbuff);
    
    TEST(" free space ", res , 6);    
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 

	CbuffDestroy(cbuff);
}
