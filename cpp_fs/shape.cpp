#include <iostream>

namespace ilrd
{

class Shape
{
public:
    Shape():m_cord(0){}
    virtual void Draw() const = 0;
    void Move(size_t move_by);
    void PrintSpaces() const;
private:
    size_t m_cord;
};

class Line:public Shape
{
public:
    Line(size_t length = 0):m_length(length){}
    virtual void Draw() const;
    size_t GetLineLength() const;
private:
    size_t m_length;
};

class Circle:public Shape
{
public:
    Circle(size_t radius):m_rdius(radius){}
    virtual void Draw() const;
private:
    Line m_rdius;
};

class Rectangle:public Shape
{
public:
    Rectangle(size_t width = 0, size_t hight = 0): m_width(width), m_hight(hight){}
    virtual void Draw() const;
private:
    Line m_width;
    Line m_hight;
};

class Square:public Shape
{
public:
    Square(size_t edge):m_edge(edge){}
    virtual void Draw() const;
private:
    Line m_edge;
};

size_t Line::GetLineLength() const
{
    return (m_length);
}


void Shape:: Move(size_t move_by)
{
    m_cord += move_by;
}

void Shape:: PrintSpaces() const
{
    for (size_t i = 0; i < m_cord; ++i)
    {
        std::cout<<" ";
    }
}

void Line:: Draw() const
{
    PrintSpaces();
    std::cout<<"Line length: "<< m_length<<"\n";
}

void Circle:: Draw() const
{
    PrintSpaces();
    std::cout<<"Circle with raduis: " << m_rdius.GetLineLength()<<"\n";
}

void Rectangle:: Draw() const
{
    PrintSpaces();
    std::cout<<"Rectangle with hight: "<<m_hight.GetLineLength()<<"and width: "<<m_width.GetLineLength()<<std::endl;   
}

void Square:: Draw() const
{
    PrintSpaces();
    std::cout<<"Square with edge: "<<m_edge.GetLineLength()<<"\n";
}

}
#define SIZE 20
int main()
{
    ilrd::Shape *array[SIZE] = {0};
    for (int i = 0, j = 1, k = 2, m = 3; m < SIZE; i += 4, j += 4, k += 4, m += 4)
    {
        array[i] = new ilrd::Circle(i); 
        array[j] = new ilrd::Line(j); 
        array[k] = new ilrd::Square(k); 
        array[m] = new ilrd::Rectangle(m); 
    }

    for (int i = 0; i < SIZE; ++i)
    {
        array[i]->Draw();
    }


    for (int i = 0; i < SIZE; ++i)
    {
        array[i]->Move(2);
    }


    for (int i = 0; i < SIZE; ++i)
    {
        array[i]->Draw();
    }

    return 0;

}