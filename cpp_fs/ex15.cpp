#include <iostream>
using namespace std;

template <typename T>
T Max(T t1, T t2)
{
    return (t1 > t2) ? t1: t2;
}

int main()
{
    int arr[12];
    size_t a = 8;
    float f = 2.2;

    cout<<Max(3,5)<<" "<<Max(3.7, 3.9)<<" ";
    cout<<Max(arr, arr + 8)<<endl;
    cout<<Max(a, a + 2)<<" "<<Max(f, (float)(f + 0.3))<<endl;
    cout<<Max('a', 'b')<<endl;
    cout<<arr;

    return 0;
}