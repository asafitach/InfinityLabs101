#include <stdio.h>

void swaping(size_t *a, size_t *b);

int main()
{
    size_t a = 1;
    size_t b = 2;
    int ia=1;
    int ib=2;
    size_t *p2a = &a;
    size_t *p2b = &b;
    swaping(&p2a, &p2b);
    swaping(p2a, p2b);
    swaping(&ia, &ib);
    
    return (0);
}

void swaping(size_t *a, size_t *b)
{
    size_t *tmp = *a;
    *a = *b;
    *b = tmp;
}

