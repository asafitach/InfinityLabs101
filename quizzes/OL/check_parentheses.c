#include <stdio.h>
#include <string.h>	
#include <stdlib.h>


char *RecursiveCheck(char *str, char check)
{	
char * cur = NULL;
	check = (check == '(') ? ')': check;
	check = (check == '{') ? '}': check;
	check = (check == '[') ? ']': check;	
	
	while (0 != *str)
	{
		if (*str == '(' || *str == '[' || *str == '{')
		{ 
			str = RecursiveCheck(str + 1, *str);	
			if (NULL == str)
			{
				return (NULL);
			}
		}
		else if (*str == ')' || *str == ']' || *str == '}')
		{
			if (*str == check)
			{
				return (str);
			}
			else
			{
				return (NULL);
			}
		}
		str++;
		
	}
	
	return (0);
}


int CheckParentheses(char *str)
{	
	
	while (0 != *str)
	{
		if (*str == '(' || *str == '[' || *str == '{')
		{
			str = RecursiveCheck(str + 1, *str);
			if (NULL == str)
			{
				return (0);
			}
		}
		else if (*str == ')' || *str == ']' || *str == '}')
		{
			return (0);
		}
		
		str++;
	}
	return (1);
}



typedef struct stack
{
	char *arr;
	int index;
}stack_t;

stack_t *Create(int size)
{
	stack_t *stack = malloc(sizeof(stack_t));
	stack->arr = malloc(sizeof(char) * size);
	stack->index = 0;
	return (stack);
}

void Push (stack_t *stack, char insert)
{
	stack->arr[stack->index] = insert;
	++stack->index;
}

char Pop(stack_t *stack)
{
	--stack->index;
	return (stack->arr[stack->index]);
}

void Destroy(stack_t *stack)
{
	free(stack->arr);
	free(stack);
	stack = NULL;
}

int IsEmpty(stack_t *stack)
{
	return ((stack->index) == 0);
}

int CheckParren(char *str)
{
	stack_t *stack = Create(strlen(str));
	char lut[256] = {0};
	lut['['] = ']';
	lut['{'] = '}';
	lut['('] = ')';

	while (str != 0)
	{
		if (*str == '(' || *str == '[' || *str == '{')
		{
			Push(stack, *str);
		}
		else if (*str == ')' || *str == ']' || *str == '}')
		{
			if (IsEmpty(stack) && *str != lut[Pop(stack)])
			{
				return 0;
			}
			else if (!IsEmpty(stack))
			{
				return 0;
			}
			
		}
		
		str++;
	}

	if (IsEmpty(stack))
	{
		Destroy(stack);
		return 0;
	}
	

	Destroy(stack);
	return 1;
}


int main()
{
	char str[16];
	strcpy(str, "{([])}");
	printf("%s: %d\n", str, CheckParentheses(str));
	printf("%s: %d\n", str, CheckParren(str));
	strcpy(str, "h{jsdkj(sd[d])}");
	printf("%s: %d\n", str, CheckParentheses(str));
	printf("%s: %d\n", str, CheckParren(str));
	strcpy(str, "hjsdkjs(d[d])}");
	printf("%s: %d\n", str, CheckParentheses(str));
	printf("%s: %d\n", str, CheckParren(str));

	return (0);
}