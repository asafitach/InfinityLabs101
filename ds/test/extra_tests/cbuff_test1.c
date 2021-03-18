#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include "cbuff.h"

#define RED "\33[1;5;31m"
#define GREEN "\33[1;32m"
#define WHIT "\33[0m"
#define MAG "\33[1;96m"
#define YEL "\33[1;33m"

#define TEST(testName,real,expected)\
            (real == expected ?\
                printf("%s:" GREEN" PASS\n"WHIT, testName) :\
                printf("%s:"  RED" FAIL\n"WHIT, testName))
               
#define TEST_NOT(testName,real,expected)\
            (real != expected ?\
                printf("%s:" GREEN" PASS\n"WHIT, testName) :\
                printf("%s:"  RED" FAIL\n"WHIT, testName))           
                
typedef enum 
{
	SUCCESS = 0,
	FAIL = 1
} status_t;  
                           
status_t TestString(); 
static cbuff_t *TestCreate(cbuff_t *cbuff);
static void TestIEmpty(cbuff_t *cbuff);
static void TestWrite(cbuff_t *cbuff, const void *src, size_t num);
static void TestRead(cbuff_t *cbuff, char *dest, size_t num);
static void TestFreeSpace(cbuff_t *cbuff);
static void TestCountFull(cbuff_t *cbuff);

int main()
{     
 	printf(MAG"\tTest string:\n"WHIT);
	TEST(MAG"The test complete succesfuly", TestString(), 0);
    
    return 0; 
}

status_t TestString()
{
	cbuff_t *cbuff = NULL;
	char dest[36] = {'\0'};
	const void *src = "here";
	
	cbuff = TestCreate(cbuff);
	TestIEmpty(cbuff);
	TestWrite(cbuff, src, 4);
	TestCountFull(cbuff);
	TestFreeSpace(cbuff);
	CbuffWrite(cbuff, " i am will you send me an angel", 31);
 	printf(MAG"\tWrite 31 byte:\n"WHIT);	
	TEST("buffer is full write 0 byte ", CbuffWrite(cbuff, "here", 4), 0);	
 	TestRead(cbuff, dest, 35);
  	printf(MAG"\tread 5 byte:\n"WHIT);		  
	TEST("buffer is empety read 0 byte ", CbuffRead(cbuff, (void *)dest, 5), 0);	     
    CbuffDestroy(cbuff);
    
    return SUCCESS;
}

static cbuff_t *TestCreate(cbuff_t *cbuff)
{
	size_t capacity = 35;	
	
	printf(MAG"Test create:\n"WHIT);		
	cbuff = CbuffCreate(capacity);
	TEST_NOT("The buffer created", cbuff, NULL);	
	
	return cbuff;
}

static void TestIEmpty(cbuff_t *cbuff)
{
	assert(NULL != cbuff);
	
	printf(MAG"Test is empty:\n"WHIT);	
	TEST("The buffer is empty", CbuffIsEmpty(cbuff), 1);
}

static void TestWrite(cbuff_t *cbuff, const void *src, size_t num)
{
	size_t write = 0;
	
	assert(NULL != cbuff);
			
	printf(MAG"Test write:\n"WHIT);			
	write = CbuffWrite(cbuff, src, num);
	TEST("write 5 byte ", write, num);
}

static void TestRead(cbuff_t *cbuff, char *dest, size_t num)
{
	size_t read = 0;
	
	assert(NULL != cbuff);
		
	printf(MAG"Test read:\n"WHIT);			
    read = CbuffRead(cbuff, (void *)dest, num);
    TEST("read from buffer 35 byte ", read, num);
    printf(YEL"%s"WHIT, dest);
    printf("\n");
}

static void TestCountFull(cbuff_t *cbuff)
{
	assert(NULL != cbuff);
	
	printf(MAG"Test count full:\n"WHIT);	
    TEST("The buffer full in 5 byte ", CbuffCountFull(cbuff), 4);	
}

static void TestFreeSpace(cbuff_t *cbuff)
{
	assert(NULL != cbuff);
	
	printf(MAG"Test free space:\n"WHIT);	
    TEST("The buffer have 31 byte free space ", CbuffFreeSpace(cbuff), 31);	
}
