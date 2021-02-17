void swaping(size_t* a,size_t* b);

int main()
{
    int a = 1;
    int b = 2;
    swaping(&a, &b);

    return (0);
}


/*swaps the value of 2 variables*/
void swaping(size_t* a, size_t* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
