#include <iostream>
#include "stack.hpp"

int main()
{
    Stack<int, 5> stack1;
    stack1.Push(23);
    stack1.Push(25);
    stack1.Push(24);
    stack1.Push(20);

    std::cout<<"stack Peek: \n";
    std::cout<<stack1.Pop()<<std::endl;

    std::cout<<"stack Peek: \n";
    std::cout<<stack1.Pop()<<std::endl;

    std::cout<<"stack Peek: \n";
    std::cout<<stack1.Pop()<<std::endl;

    std::cout<<"stack Peek: \n";
    std::cout<<stack1.Pop()<<std::endl;


    return 0;
}