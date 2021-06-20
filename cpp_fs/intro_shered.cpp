#include <iostream>
using namespace std;

void OtherFoo(int c)
{
    cout<<"I'm shared foo"<<c<<endl;
}

void FooInRunTime(int c)
{
    cout<<"Load in run time"<<c<<endl;
}