#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/

#include ".h"

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
    printf(CYAN"\tTest \n\n"WHITE); 
    
    TEST("  ", 1 , 1); 
    
    TEST("  ", 1 , 1); 
    
    TEST("  ", 1 , 1); 
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 
}
