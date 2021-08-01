

char *StrCpy(char *dest, const char *src)
{
	char *dest_start = dest;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	while ('\0' != *src)
	{
		*dest = *src;
		++src;
		++dest;
	}
	
	*dest = '\0';
	
	return (dest_start);
}


#define SIZE 4

int main()
{
	int arr1[SIZE] = {1, 2, 3, 4};
	int arr2[SIZE] = {5, 5, 10, 15};
	
	StrCpy((char *)arr1, (const char *)arr2);
}



void PrintData(void *data)
{
	char *runner = (char *)data;
	
	printf("%d\n", *(int *)runner);
	runner = ((int *)runner) + 1;
	printf("%d\n", *(int *)runner);
	runner += 4;
	printf("%c\n", *runner);
	++runner;
	printf("%f\n", *(float *)runner);
}

#define ASCII 256

void PrintDifferChars(char *arr1, char *arr2, size_t size)
{
	char lut[ASCII] = {0};
	size_t index = 0;
	char tmp = 0;
	
	for (index = 0; index < size; ++index)
	{
		lut[arr1[index]] = 1;
	}
	
	for (index = 0; index < size; ++index)
	{
		tmp = arr2[index];
		if (0 == lut[(int)tmp])
		{
			printf("%c\t", tmp);
		}
		else
		{
			lut[(int)tmp] = 0;
		}
	}
	
	printf("\nin the first array\n");
	for (index = 0; index < ASCII; ++index)
	{
		if (1 == lut[index])
		{
			printf("%c\t", (char)index);
		}
	}
	
}
	

int Add7thBitAnd6thBit(int num)
{
	return ((num >> 5) & 3));
} 


#define BYTE 8
char LongThirdByte(long num)
{
	num <<= (sizeof(long) - 3) * BYTE);
	num >>= ((sizeof(long) - 1) * BYTE);
	
	return (*(char *)&num);
} 




















	
	
