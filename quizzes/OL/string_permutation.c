#include <stdio.h>

void Swap(char *str, size_t letter, size_t index);

void PrintPemutetion(char *str, size_t index, size_t len)
{
    static int counter = 0;
    size_t letter = 0;

    if (index == len)
    {
        ++counter;
        printf("permutation nu. %d is %s\n", counter, str);
    }

    else
    {
        for (letter = index; letter < len; ++letter)
        {
            Swap(str, letter, index);
            PrintPemutetion(str, index + 1, len);
            Swap(str, letter, index);
        }
    }
}

void Swap(char *str, size_t letter, size_t index)
{
    char tmp = str[letter];
    str[letter] = str[index];
    str[index] = tmp; 
}

int main()
{
    char str[] = "12345";
    PrintPemutetion(str, 0, 5);

    return (0);
}



