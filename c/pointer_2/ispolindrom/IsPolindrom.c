#include "IsPolindrom.h" 

int IsPolindrom (const char * str)
{
	int size=StrLen(str);
	int i=0;

	for(i=0;i<size/2;i++)
	{
		if(*(str+i)!=*(str+size-i-1))
		{
			return(0);
		}
	}
	return(1);
}

int StrLen (const char *str)
{
	int count = 0;
	while(*(str+count))
	{
		count++;
	}
	return(count);
}

