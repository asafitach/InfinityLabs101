#include <iostream>
#include <dlfcn.h>
/* #define _GNU_SOURCE
 */

using namespace std;

extern void OtherFoo(int c);

void Foo(void *)
{
    cout<<"defualt functoin\n";
}

void Foo()
{
    cout<<"I have no atgs\n";
}

void Foo(int i)
{
    cout<<"I have a int:"<<i<<" \n";
}

void Foo(char *c)
{
    cout<<"I have a char:"<<*   c<<" \n";
}


int main()
{
    int i = 55;
    char c = 'f';
    Foo();
    Foo(&i);
    Foo(&c);
    Foo((size_t *)&i);
    Foo((size_t *)&c);
/*     Foo((char)49);
    Foo(0xfff32); */
    OtherFoo(i);
    FILE *fp = (FILE*)dlopen("intro_shared.o", RTLD_LAZY);
    void (*fun)(int c) = (void(*)(int))dlsym(fp, "FooInRunTime");
    fun(i);

    return (0);
}