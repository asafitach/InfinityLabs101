/*****************        Reviewed by Rachel       **************************/
#include <stdio.h>/*printf*/
#include "ex2.h"


int table[KEY];


void InitTable ()
{		
	int index = 0;
	
	for(index = 0; index < KEY; index++)
	{
		table[index] = 1;
	}
}

void StrInTable(char *str, int num)
{
	while(*str)
	{
		table[(short)*str] *= num;
		str++;
	}
}

void PrintLetters()
{
	int index = 0;
	
	for(index = 0; index < KEY; index++)
	{
		if((table[index] % 3 == 0) && (table[index] % 5 == 0) /*2 rows cond'*/
		&& (table[index] % 7 != 0))
		{
			printf("%c", index);	
		}
	}
	printf("\n");
}	


void StrCmp3(char *str1, char *str2, char *str3)
{	
	InitTable();
	StrInTable(str1, 3);
	StrInTable(str2, 5);
	StrInTable(str3, 7);
	PrintLetters();
}
