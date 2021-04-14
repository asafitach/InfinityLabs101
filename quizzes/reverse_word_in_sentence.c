#include <stdio.h>
#include <string.h>

void ReverseWordInSentence(char sentence[]);

int main()
{
	char sentence[] = "hello from the end";
	printf("before\n%s\n", sentence);
	ReverseWordInSentence(sentence);
	printf("after\n%s\n", sentence);
	
	return 0;
}


void Reverse(char *str, size_t len)
{
	size_t index = 0;
	char chr = 0;
	
	for (index = 0; index < len / 2; ++index)
	{
		chr = str[index];
		str[index] = str[len - index];
		str[len - index] = chr;
	}
}
void ReverseWordInSentence(char sentence[])
{
	size_t count = 0;
	size_t index = 0;
	
	while (0 != sentence[index])
	{
		while (' ' != sentence[index] && sentence != NULL)
		{
			++count;
			++index;
		}
		Reverse(sentence + index - count - 1, count - 1);
		++index;
	}
	
	Reverse(sentence, strlen(sentence));
}

