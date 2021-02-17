#include<stdio.h>
#include<stdlib.h>
#include "string.h" 

int main ()
{
	char str1[100]= "abcdEf";
	char in_str1[]="cdE";
	char str11[]= "AbCdEf";
	char str2[]= "mnfol";
	char * ptr= NULL;
	char c= 'd';
	int get=0;

	get=StrLen(str1);
	printf("the number shuold be 6 get=%d \n", get);
	ptr=StrDup(str2);
	printf("the or is %s the dup is %s \n", str2, ptr);
	free(ptr);
	ptr=StrCpy(ptr, str1);
	printf("the or is %s the copy is %s \n", str1, ptr);
	ptr= StrnCpy(ptr, str1, 3);
	printf("the src is %s the cpy shuld be 3 letters %s \n", str1, ptr);
	ptr=StrChr(str1, c);
	printf("the original string is %s after search dor d is %s \n", str1, ptr);
	get=StrCaseCmp(str1, str11);
	printf("this should be 0 please be! %d \n", get);
	StrCat(str1, str11);
	printf("sould be abcdEfAbCdEf: %s \n", str1);
	ptr=StrnCat(str1, str11, 2);
	printf("sould be abcdEfAb: %s \n", str1);
	ptr=StrStr(str1, in_str1);
	printf("the hay is %s the needle found is %s \n", str1, ptr);
	get=(size_t)StrSpn(str1, in_str1);
	printf("the full str is %s the num is (please be 3) %d", str1, get);
	

return (0);
}




