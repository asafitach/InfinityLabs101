/*****************        Reviewed by --------       **************************/
#include <stdlib.h>/*calloc*/
#include <stdio.h>/*printf*/
#include "ex1.h"

static int arr[256];
static char index_s[36];


void InitLutInt()
{
	int i = 0;
	int count = 0;
	for(i = 0; i < 256; i++)
	{
		arr[i] = 0;
	}
	for(i = '0'; i <= '9'; i++, count++)
	{
		arr[i] = count;
	}
	for(i = 'A'; i <= 'Z'; i++, count++)
	{
		arr[i] = count;
		arr[i + 32] = count;
	}
}

void InitLutChar()
{
	int i = 0;
	for(i = 0; i < 10; i++)
	{
		index_s[i] ='0' + i;
	}
	for(i = 10; i < 37; i++)
	{
		index_s[i] = 'A' +i;
	}
}

int IsInBase(char a, const int base)
{
	return ((base>arr[(unsigned int) a]) ? (arr[(unsigned int) a]):(-1));
}

	
int Atoi(const char *str, const int base)
{
	int val = 0;
	int sign = 1;
	
	if(base < 1)
	{
		printf("ERROR - base must be posetive\n");
		return (0);
	
	}
	
	InitLutInt();
	if(*str == '-')
	{
		sign = -1;
		str++;
	}
	
	while(*(str))
	{
		if(0 > IsInBase(*str, base))
		{
			return (0);
		}
		val *= base;
		val += IsInBase(*str, base);
		str++;
	}

	return (val * sign);
}

size_t CountDigit( int num, int base)
{
	size_t count = 0;
	
	if(num == 0)
	{
		return (1);
	}

	while(num)
	{
		count++;
		num /= base;
	}

	return (count);
}

char *ItoA1 (int num)
{
	char *str = NULL;
	int index = 0;
	int size = num;

	if(num < 0)
	{
		size = -size + 1;
	}
	str = (char*)calloc(size + 1, sizeof(char));
	if(str == NULL)
	{
		printf("Allocation failed\n");
		return (NULL);
	}
	
	if(num < 0)
	{
		num = -num;
		*str = '-';
		str++;
	}
	for(index = 0; index < num; index++, str++)
	{
		*str = '1';
	}
	return(str-size);
}



char *Itoa (int num, int base)
{
	char *str = NULL;
	size_t size = 0;
	size_t index = 0;
	int flag = num;
	
	if(base < 1)
	{
		printf("ERROR, base must be posetive\n");
		return(str);
	}
	if(base == 1)
	{
		str = ItoA1(num);
		return (str);
	}
	
	
	InitLutChar();
	size = CountDigit(num, base);
	if(num < 0)
	{
		size++;
		num = -num;
	}
	
	str = (char*)calloc(size + 1, sizeof(char));
	if(str == NULL)
	{
		printf("Allocation failed");
		return (NULL);
	}

	for(index = size ; index ; index--, num /= base)
	{
		*(str + index - 1) = index_s[num % base];
	}
	if(flag < 0)
	{
		*str = '-';
	}

	return (str);
}


int AToI(const char *str)
{
	int val = 0;
	int sign = 1;

	if(*str == '-')
	{
		sign = -1;
		str++;
	}
	
	while(*(str))
	{
		if((*(str) > 47) && (*(str) < 58))
		{
			val*=10;
			val += *(str) - '0';
			str++;
		}
		else
		{
			return (0);
		}
	}

	return (val * sign);
}

size_t CountDigit1( int num)
{
	size_t count = 0;
	
	if(num == 0)
	{
		return (1);
	}

	while(num)
	{
		count++;
		num /= 10;
	}

	return (count);
}

char *IToA (int num)
{
	char *str = NULL;
	size_t size = 0;
	size_t index = 0;
	int flag = num;

	size = CountDigit1(num);
	if(num < 0)
	{
		size++;
		num = -num;
	}
	
	str = (char*)calloc(size + 1, sizeof(char));
	if(str == NULL)
	{
		printf("Allocation failed");
		return (NULL);
	}

	for(index = size ; index ; index--, num /= 10)
	{
		*(str + index - 1) = (num % 10) + '0';
	}
	if(flag < 0)
	{
		*str = '-';
	}

	return (str);
}












