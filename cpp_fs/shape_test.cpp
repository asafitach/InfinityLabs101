#include "shape.hpp"

int main()
{
    const int size = 20;
    ilrd::Shape *shapes[size] = {0};
    for (int i = 0, j = 1, k = 2, m = 3; m < size; i += 4, j += 4, k += 4, m += 4)
    {
        shapes[i] = new ilrd::Circle(i); 
        shapes[j] = new ilrd::Line(j); 
        shapes[k] = new ilrd::Square(k); 
        shapes[m] = new ilrd::Rectangle(m); 
    }

    for (int i = 0; i < size; ++i)
    {
        shapes[i]->Draw();
    }


    for (int i = 0; i < size; ++i)
    {
        shapes[i]->Move(2);
    }


    for (int i = 0; i < size; ++i)
    {
        shapes[i]->Draw();
    }

    return (0);

}