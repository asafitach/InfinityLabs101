/*****************        Reviewed by --------       **************************/
#include <stdio.h>/*printf*/
#include <stdlib.h>/*free*/
#include "ex1.h"


void Test_Atoi();
void Test_Itoa();




int main()
{
	Test_Atoi();
	Test_Itoa();


	return (0);
}









void Test_Atoi()
{
	char *num1 = "3f";
	char *num2 = "-013804";
	char *str = "skdfj99";

	printf("base: 30 3f = %d\n", Atoi(num1, 30));
	printf("base: 2 3f = %d\n", Atoi(num1, 2));
	printf("base: 16 3f = %d\n", Atoi(num1, 16));
	printf("base: 10 3f = %d\n", AToI(num1));

	printf("base: 10 -013804 = %d\n", Atoi(num2, 10));
	printf("base: 10 -013804 = %d\n", AToI(num2));
	printf("base: 9 -013804 = %d\n", Atoi(num2, 9));
	printf("base: 5 -013804 = %d\n", Atoi(num2, 5));
	printf("base: 10 -013804 = %d\n", AToI(num2));


	printf("base: 36 skdfj99 = %d\n\n", Atoi(str, 36));
	printf("base: 22 skdfj99 = %d\n\n", Atoi(str, 22));
	printf("base: 10 skdfj99 = %d\n\n", Atoi(str, 10));
	printf("lib atoi: skdfj99 = %d\n\n", atoi(str));
	printf("base: 10 skdfj99 = %d\n\n", AToI(str));



	return;
}

void Test_Itoa ()
{
	char *ptr = NULL;
	int num1 = -132;
	int num2 = 193894;
	int num3 = 0;
	
	ptr= Itoa(num1, 10);
	printf("-132 = %s\n",ptr);
	free(ptr);
	ptr= IToA(num1);
	printf("-132 = %s\n",ptr);
	free(ptr);
	ptr= Itoa(num1, 1);
	printf("-132 = %s\n",ptr);
	free(ptr);
	ptr= Itoa(num1, 16);
	printf("-132 = %s\n",ptr);
	free(ptr);

	ptr = Itoa(num2, 10);
	printf("193894 = %s\n", ptr);
	free(ptr);
	ptr = IToA(num2);
	printf("193894 = %s\n", ptr);
	free(ptr);
	ptr = Itoa(num3, 10);
	printf("0 = %s\n\n", ptr);
	free(ptr);
	ptr = IToA(num3);
	printf("0 = %s\n\n", ptr);
	free(ptr);


return;
}













