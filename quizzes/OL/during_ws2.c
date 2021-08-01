#include <stdio.h>
#include <string.h>

void TFPrint(int number)
{
	int index = 1;
	int num = (number > 0) ? number : -number;
	
	while (index < (num + 1))
	{
		if (0 == index % 3)
		{
			printf("T");
		}
		if (0 == index % 5)
		{
			printf("F");
		}
		if (0 != index % 5 && 0 != index % 3)
		{
			printf("%d", index);
		}
		printf("\n");
		index++;
	}
}

char Tolower(char chr)
{
	if (chr >= 'A' && chr <= 'Z')
	{
		return (chr + 32);
	}
	return (chr);
}

void ReverseStr(char *str)
{
	size_t size = strlen(str);
	size_t index = 0;
	char tmp= 0;

	printf("%s\n", str);
	
	for (index = 0; index < size/2; index++)
	{
		tmp = Tolower(*(str + index));
		*(str + index) = Tolower(*(str + size - index - 1));
		*(str + size - index - 1) = tmp;
	}
	
	printf("%s\n", str);
	
}


int main()
{
	int number = 0;
	char str[] = "HelLo WorlD!";
	
	printf("Enter anumber\n");
	scanf("%d", &number);
	
	TFPrint(number);
	ReverseStr(str);
	
	return (0);
}
