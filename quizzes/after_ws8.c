#include <stdio.h>

#define MAX2(a, b) ((a>b) ? (a) : (b))
#define MAX3(a, b, c) (MAX2(MAX2(a, b), c))
#define TO_LOWER(a) ((c > 64) && (c < 97) ? (c + 32) : (c))
#define OFFSET(s, f) ((char*)f - (char*)s)

int main()
{
	int size = 0;
	struct a1{
	int a;
	char b;
	int *p;
	char c;
	} a11;

	struct b1{
	int a;
	char b[5];
	}b11;

	size = sizeof(a11);
	printf("size of (int, char, pointer, char) is : %d\n", size);
	size = sizeof(b11);
	printf("size of (int, char[5]) is : %d\n", size);
	return 0;
}
