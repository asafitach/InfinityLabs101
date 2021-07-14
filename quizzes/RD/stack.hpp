#ifndef ILRD_RD101_STACK_HPP
#define ILRD_RD101_STACK_HPP

#include <cstdlib>

template <typename T, int SIZE>
class Stack
{
public:
    explicit Stack();
    Stack(Stack &other);
    Stack & operator=(Stack &other);
    virtual ~Stack();

    void Push(T data);
    T Pop();
    T Peek()const;

private:
    T m_array[SIZE];
    size_t m_index;
};

template <typename T, int SIZE>
Stack<T, SIZE>::Stack(): m_index(0)
{
}

template <typename T, int SIZE>
Stack<T, SIZE>::~Stack()
{
}

template <typename T, int SIZE>
void Stack<T, SIZE>::Push(T data)
{
    if (m_index == SIZE)
    {
        throw std::out_of_range ("full stack!");
    }
    m_array[m_index] = data;
    ++m_index;
}

template <typename T, int SIZE>
T Stack<T, SIZE>::Pop()
{
    if (0 == m_index)
    {
        throw std::out_of_range ("empty!");
    }
    --m_index;
    return (m_array[m_index]);
}


template <typename T, int SIZE>
T Stack<T, SIZE>::Peek() const
{
    if (0 == m_index)
    {
        throw std::out_of_range ("empty!");
    }
    return (m_array[m_index - 1]);
}

template<class T, int SIZE> 
Stack<T, SIZE>::Stack(Stack<T, SIZE> &other)
{
    for (int i = 0; i < other.m_index; ++i)
    {
        m_array[i] = other.m_array[i];
    }
    m_index = other.m_index;
}

template<class T, int SIZE> 
Stack<T, SIZE>& Stack<T, SIZE>::operator=(Stack<T, SIZE> &other)
{
    for (int i = 0; i < other.m_index; ++i)
    {
        m_array[i] = other.m_array[i];
    }
    m_index = other.m_index;
    return *this;
}

#endif //ILRD_RD101_STACK_HPP