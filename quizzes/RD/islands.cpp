#include <iostream>
#include <cassert>
using namespace std;

#define SIZE 5

void Zero(int arr[SIZE][SIZE], int row, int col, int size)
{
    if (row >= size || row < 0 || col >= size || col < 0 || 0 ==arr[row][col])
    {
        return;
    }
    arr[row][col] = 0;

    Zero(arr, row, col - 1, size);
    Zero(arr, row + 1, col, size);
    Zero(arr, row, col + 1, size);
}

int NumOfIslands(int arr[SIZE][SIZE], int size)
{
    assert(NULL != arr);
    assert(0 < size);

    for (int row = 0; row < size; row += (size - 1))
    {
        for (int col = 0; col < size; ++col)
        {
            if (1 == arr[row][col])
            {
                Zero(arr, row, col, size);
            }
            if (1 == arr[col][row])
            {
                Zero(arr, col, row, size);
            }
        }
    }

        int counter = 0;
    for (int row = 1; row < size; ++row)
    {
        for (int col = 1; col < size; ++col)
        {
            if (1 == arr[row][col])
            {
                ++counter;
                Zero(arr, row, col, size);
            }
        }
    }

    return (counter);
}


int main()
{
    int arr[SIZE][SIZE] = {{0,0,1,0,0}, {0,1,0,0,0}, {1,0,1,0,0}, {1,0,1,0,0}, {1,0,0,1,0}};

    cout<<NumOfIslands(arr, SIZE)<<endl;

    return 0;
}