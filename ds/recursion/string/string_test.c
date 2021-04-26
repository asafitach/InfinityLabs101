#include <stdio.h>   /* printf */
#include <string.h>   /* strlen strcmp strcpy strcat strstr */

#include "string.h"

/***********************color macros for printf*********************************/

#define RED "\033[1;31m"  /* print in red */

#define GREEN "\033[1;5;32m"	/* print in green */

#define BLUE "\033[1;34m"  /* print in blue */

#define YELLOW "\033[1;4:1;33m" /* print in yellow  */

#define PURPLE "\033[1;35m" /* print in purple */

#define CYAN "\033[1;3;36m" /* print in cyan */

#define RESET "\033[0m" /* reset print color  */

/**********************************Test MACROs*********************************/

#define TEST_ARE_EQUAL(name, real, expected) printf("%s: %s\n", name, real == expected\
									? GREEN"SUCCESS\n"RESET\
									: RED"\aFAILURE\n"RESET)
									
/********************* Test functions signitures ***************************/

static void testStrLen(void);
static void testStrCmp(void);
static void testStrCpy(void);
static void testStrCat(void);
static void testStrStr(void);

/********************* main ***************************/

int main ()
{
	testStrLen();
	
	testStrCmp();
	
	testStrCpy();
	
	testStrCat();
	
	testStrStr();

	return (0);
}

/********************* testStrLen ***************************/

void testStrLen(void)
{
	char *str = "Hello";
	
	int sys_res = strlen(str);
	
	int my_res = StrLen(str);
	
	TEST_ARE_EQUAL("Test StrLen vs strlen", my_res, sys_res);
	
	return ;
}

/********************* testStrCmp ***************************/

void testStrCmp(void)
{
	char *str1 = "Hello";
	
	char *str2 = "Hello";
	
	char *str3 = "Helld";
	
	char *str4 = "Hello";
	
	int sys_res1 = strcmp(str1, str2);
	
	int my_res1 = StrCmp(str1, str2);
	
	int sys_res2 = strcmp(str4, str3);
	
	int my_res2 = StrCmp(str4, str3);
	
	TEST_ARE_EQUAL("Test no. 1: StrCmp vs strcmp", my_res1, sys_res1);
	
	TEST_ARE_EQUAL("Test no. 2: StrCmp vs strcmp", my_res2, sys_res2);
	
	return ;
}

/********************* testStrCpy ***************************/

void testStrCpy(void)
{
	char *src = "Hello";
	
	char dest1[100] = {0};
	char dest2[100] ={0};
	
	strcpy(dest1, src);
	
	StrCpy(dest2, src);
	
	TEST_ARE_EQUAL("Test StrCpy vs strcpy", StrCmp(dest1, dest2), 0);
	
	return;
}

/********************* testStrCat ***************************/

void testStrCat(void)
{
	char src[] = "World";
	
	char dest1[100] = "Hello";
	char dest2[100] = "Hello";
	
	strcat(dest1, src);
	
	StrCat(dest2, src);
	
	TEST_ARE_EQUAL("Test StrCat vs strcat", StrCmp(dest1, dest2), 0);
	
	return ;
}

/********************* testStrStr ***************************/

void testStrStr(void)
{
    char *haystack = "aakgnaa";

    char *needle = "kgn";

    char *sys_res = strstr(haystack, needle);

    char *my_res = StrStr(haystack, needle);

    TEST_ARE_EQUAL("Test StrStr vs strstr", strncmp(sys_res, my_res, strlen(needle)), 0);

    return ;
}

/********************* end ***************************/


