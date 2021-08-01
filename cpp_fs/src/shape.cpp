#include <iostream>
#include "shape.hpp"

namespace ilrd
{

Shape::Shape& ():m_cord
{}

Line::Line&(size_t length):m_length(length)
{}

Circle::Circle&(size_t radius):m_radius(radius)
{}

Rectangle::Rectangle&(size_t width, size_t hight): m_width(width), m_hight(hight)
{}

Square::Square&(size_t edge):m_edge(edge)
{}
  

void Shape:: Draw() const
{
    for (size_t i = 0; i < m_cord; ++i)
    {
        std::cout<<" ";
    }
}

void Line:: Draw() const
{
    Shape::Draw();
    std::cout<<"Line length: "<< m_length<<std::endl;
}

void Circle:: Draw() const
{
    Shape::Draw();
    std::cout<<"Circle with raduis: " << m_radius<<std::endl;
}

void Rectangle:: Draw() const
{
    Shape::Draw();
    std::cout<<"Rectangle with hight: "<<m_hight.GetLineLength()<<" and width: "<<m_width.GetLineLength()<<std::endl;
}

void Square:: Draw() const
{
    Shape::Draw();
    std::cout<<"Square with edge: "<<m_edge.GetLineLength()<<std::endl;
}

}
