#include<stdio.h>
#include"if_else"

void Initialize ((**fun_arr)(), int size)
{
int i=0;
for(i=0; i<size; i++)
{
*(fun_arr+i)=&Empy;
}
*(fun_arr+'A')=&APressed;
*(fun_arr+'a')=&APressed;
*(fun_arr+'T')=&TPressed;
*(fun_arr+'t')=&TPressed;
*(fun_arr+ 27)=&EscPressed;

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

void Tpressed()
{
	printf("T pressed \n");
}

void EscPressed()
{
	exit;
}

