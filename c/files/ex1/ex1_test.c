#include"ex1.h"


int main()
{

	int index=0;


	struct print_me array[10];
	Init(array, 10);


	for(index=0; index<10;index++)
	{
		(*(array[index].ptr)) (array[index].var);
	}


	return (0);
}



