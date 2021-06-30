#ifndef ILRD_RD101_SHAPE_HPP
#define ILRD_RD101_SHAPE_HPP

#include <cstddef>

namespace ilrd
{

class Shape
{
public:
    Shape():m_cord(0){}
    virtual void Draw() const = 0;
    void Move(size_t move_by);
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
    Circle(size_t radius = 0):m_radius(radius){}
    virtual void Draw() const;
private:
    size_t m_radius;
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
}
#endif //ILRD_RD101_SHAPE_HPP