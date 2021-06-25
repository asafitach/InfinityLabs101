#include <iostream>
#include "string.hpp"
using namespace std;
using namespace ilrd;

int main()
{
    String s1("hello");
    String s2(s1);
    s1 = s2;
    cout << "s1 length :" << s1.Length() << endl;
    cout << "s1.CStr :" << s1.CStr() << endl;
    return 0;
}