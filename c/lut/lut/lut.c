#include<stdio.h>/*printf*/
#include<stdlib.h>/*system*/
#include"lut.h"

void Initialize (void (**fun_arr)(void), int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		*(fun_arr + i)= &Empty;
	}
	*(fun_arr + 'A') = APressed;
	*(fun_arr + 'a') = APressed;
	*(fun_arr + 'T') = TPressed;
	*(fun_arr + 't') = TPressed;
	*(fun_arr +  27) = EscPressed;

	return;
}

void Empty ()
{
	return;
}

void APressed()
{
	printf("A pressed \n");
}

void TPressed()
{
	printf("T pressed \n");
}

void EscPressed()
{
	printf("EXIT");
	system("stty -icanon echo");
	exit(1);
}

