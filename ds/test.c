#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/

#include ".h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
void TestStackCreate(); 

int main()
{
    system("clear");
    
    TestStackCreate(); 
    
    return 0; 
}

void TestStackCreate()
{
    printf(CYAN"\tTest StackCreate\n\n"WHITE); 
    
    TEST("receive a pointer", (StackCreate(5)? 1:0) , 1); 
    
    printf(CYAN"\tEnd Test StackCreate\n\n"WHITE); 
}
