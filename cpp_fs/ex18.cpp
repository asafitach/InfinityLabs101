#include <iostream>
using namespace std;

void Foo(const double& d)
{
    // d = 2.2;
    cout<<d<<endl;
    cout<<&d<<endl;
    // ++d;

}

void Bar(double& d)
{
    cout<<d<<endl;
    cout<<&d<<endl;
}

int main()
{
    int i = 10;
    cout<<i<<"\n"<<&i<<endl;
    Foo(i);
    // cout<<i<<endl;
    Bar(reinterpret_cast<double&> (i));
    // cout<<i<<endl;

    return (0);
}