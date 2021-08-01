#include <stdlib.h> /* malloc calloc free */
#include <assert.h> /* assert */
#include <stdio.h>
#include <string.h>

/******************************************************************************/
int Rotate(char *str1, char *str2, int size, int f_index)
{
	int index = 0;
	
	for (index = 0; index < size; index++)
	{
		if (*(str1 + ((f_index + index) % size)) != *(str2 + index))
		{
			return (0);
		}
	}
	
	return (1);
}


int IsArrayRotate(char *str1, char *str2)
{
	int size = (strlen(str1) == strlen(str2)) ? strlen(str1) : 0;
	int index = 0;
	int ans = 0;
	
	for (index = 0; index < size; index++)
	{
		if(*(str1 + index) == *str2)
		{
			ans = Rotate(str1, str2, size, index);
			if (1 == ans)
			{
				return (1);
			}
		}
	}
	
	return (0);
}


int main()
{
	char str1[] = "hello world";
	char str2[] = "llo worldhe";
	
	printf("is %s and %s is a rotate of each oter?\n 1 for yes %d\n", str1, str2, IsArrayRotate(str1, str2));
	
	return (0);
}
/********************************E.O.F*****************************************/
