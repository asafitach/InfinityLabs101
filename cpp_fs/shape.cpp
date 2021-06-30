#include <iostream>
#include "shape.hpp"

namespace ilrd
{

size_t Line::GetLineLength() const
{
    return (m_length);
}


void Shape:: Move(size_t move_by)
{
    m_cord += move_by;
}

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
