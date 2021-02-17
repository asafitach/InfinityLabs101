#include<stdio.h>/*printf*/
#include<stdlib.h>/*system, getchar*/
#include"switch.h"


int main()
{
	int chr = 0;

	system("stty -icanon -echo");


	do
	{
		printf("please enter a key \n");
		chr=getchar();
		switch(chr)
		{
			case 'A':
				{
					printf("A pressed\n");
					break;
				}
			case 'a':
				{
					printf("A pressed\n");
					break;
				}
			case 'T':
				{
					printf("T pressed\n");
					break;
				}
			case 't':
				{
					printf("T pressed\n");
				}
		}		
	}
	while(27 != (chr));

	printf("EXIT");

	system("stty -icanon echo");

	return (0);
}
