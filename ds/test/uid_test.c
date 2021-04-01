#include <stdio.h> /*printf*/
#include <stdlib.h> /*system*/
#include <unistd.h> 

#include "uid.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected)\
    printf("%s: %s\n\n", name, actual == expected ? GREEN"Pass"WHITE : RED"Fail"WHITE)
    
void TestUid(); 

int main()
{
    system("clear");
    fork();
    TestUid(); 
    
    return 0; 
}

void TestUid()
{
    ilrd_uid_t first;
    ilrd_uid_t seconed;
    ilrd_uid_t third;
    
    printf(CYAN"\t--Test UID-- \n\n"WHITE); 
    
    first = UidCreate();
    seconed = UidCreate();
    third = UidCreate();
    
    TEST(" create + is same ", UidIsSame(first, first) , 1); 
    
    seconed = GetBadUid();
    TEST(" bad + is same ", UidIsSame(first, seconed), 0); 
    
    printf("first: counter = %lu \ntime = %ld\npid =%d\n", first.counter, first.timestamp, first.pid);
    printf("seconed (bad): counter = %lu \ntime = %ld\npid =%d\n", seconed.counter, seconed.timestamp, seconed.pid);
    printf("third: counter = %lu \ntime = %ld\npid =%d\n", third.counter, third.timestamp, third.pid);
    
    printf(CYAN"\tEnd Test \n\n"WHITE); 
}
