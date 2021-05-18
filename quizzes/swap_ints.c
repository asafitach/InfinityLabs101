void Swap1(int *x, int *y)
{
    int temp = 0;
    
    assert(NULL != x);
    assert(NULL != y);

    temp = *x;
    *x = *y;
    *y = temp;
}

void Swap2(int *x, int *y)
{
    assert(NULL != x);
    assert(NULL != y);

    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

void Swap3(int *x, int *y)
{
    int temp = *x;
    
    assert(NULL != x);
    assert(NULL != y);

    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
}

1.
pro:
simple, readable, always true
ags:
use extra space, less efficient

2.
pro:
doesn't require extra space, efficient (run-time)
ags:
doesn't so readable, we have to unsure x != y

3.
pro:
doesn't require extra space, understandable
ags:
pretty efficient but less then method 3 which require extra step using the , we have to unsure x != y