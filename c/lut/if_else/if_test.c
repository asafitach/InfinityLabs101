#include<stdio.h>/*print*/
#include<stdlib.h>/*getchar, system*/
#include"if.h"


int main()
{
	int chr = 0;

	system("stty -icanon -echo");



	do
	{
		printf("please enter a key \n");
		chr=getchar();
		if(chr=='A' || chr=='a')
		{
			printf("A pressed\n");
		}
		else if(chr=='T'||chr=='t')
		{
			printf("T pressed\n");
		}
	}
	while(27 != (chr));

	printf("EXIT");

	system("stty -icanon echo");

	return (0);
}
