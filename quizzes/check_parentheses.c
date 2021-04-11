#include <stdio.h>
#include <string.h>	


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

int main()
{
	char str[16];
	strcpy(str, "{([])}");
	printf("%s: %d\n", str, CheckParentheses(str));
	strcpy(str, "h{jsdkj(sd[d])}");
	printf("%s: %d\n", str, CheckParentheses(str));
	strcpy(str, "hjsdkjs(d[d])}");
	printf("%s: %d\n", str, CheckParentheses(str));

	return (0);
}
