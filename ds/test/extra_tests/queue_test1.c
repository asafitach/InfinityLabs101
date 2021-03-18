#include <stdio.h> /* printf */
#include <string.h> /* strcmp */
#include "queue.h"

#define RED "\33[1;5;31m"
#define GREEN "\33[1;32m"
#define WHIT "\33[0m"
#define MAG "\33[1;96m"
#define YEL "\33[1;33m"

#define TEST(testName,real,expected)\
            (real == expected ?\
                printf("%s:" GREEN" PASS\n"WHIT, testName) :\
                printf("%s:"  RED" FAIL\n"WHIT, testName))
               
static void TestInt();  
/*static void TestString(); */   

int main()
{
	TestInt();
	/*TestString(); */
	                         
	return 0;
} 
static void TestInt()
{
	queue_t *queue = NULL;
	queue_t *queue2 = NULL;
	int status = 0;
	
	printf(MAG"\tTest int:\n"WHIT);		
	queue = QueueCreate();
	printf(MAG"Test is empty:\n"WHIT);	
	TEST("The slist is empty", QueueIsEmpty(queue), 1);
	
	printf(MAG"Test list insert:\n"WHIT);
	status = Enqueue(queue,  (void *)4);
	
	TEST("The queue have one value", status, 0);
	
	Enqueue(queue, (void *)7);
	Enqueue(queue, (void *)9);
	printf(MAG"Test peek data:\n"WHIT);			
	TEST("You firs value is: 4", QueuePeek(queue), (void *)4);
	printf(MAG"Test count data:\n"WHIT);			
	TEST("The queue have 3 value", QueueCount(queue), 3);	
	
	queue2 = QueueCreate();
	Enqueue(queue2, (void *)4);
	Enqueue(queue2, (void *)8);
	QueueAppend(queue, queue2);
	printf(MAG"Test append data:\n"WHIT);			
	TEST("The queue have 5 value", QueueCount(queue), 5);
	
	Dequeue(queue);
	printf(MAG"Test dequeue data:\n"WHIT);			
	TEST("The queue have 4 value", QueueCount(queue), 4);
		

	QueueDestroy(queue);

}	                
