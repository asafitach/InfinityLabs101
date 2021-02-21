#include<stdio.h>
#include "g.h"

int main()
{
	g_s=3;
	printf("%d\n", g_s);
	Foo();
	printf("%d\n", g_s);
	return 0;
}
