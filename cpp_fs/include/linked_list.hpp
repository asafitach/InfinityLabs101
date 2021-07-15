#ifndef __LINKED_LIST_HPP
#define __LINKED_LIST_HPP

#include <iostream>
#include <cstdlib>

template <typename T>
class linked_list_interface
{
public:
    virtual T GetData() = 0;
    virtual void SetData(T new_data) = 0;
    virtual void PrintData() = 0;
};

template <typename T>
class linkedListLeaf: public linked_list_interface
{
public:
    linkedListLeaf(T data): m_data(data), m_next(new *linkedListLeaf) 
    {
        m_next = NULL:
    }
    linkedListLeaf (linkedListLeaf &other): m_data(other.m_data), m_next(new *linkedListLeaf)
    {
        m_next = other.m_next;
        other.m_next = this;
    }
    operator=(linkedListLeaf &other): m_data(other.m_data), m_next(new *linkedListLeaf)
    {
        m_next = other.m_next;
        other.m_next = this;
    }
    virtual ~linkedListLeaf()/* is it smart? if it will be used only under linked_list class it will be good, otherwise it might cause problems */
    {
        delete[] m_next;
    }

    virtual T& GetData()const
    {
        return (m_data);
    }
    virtual void SetData(T new_data)
    {
        m_data = new_data;
    }
    virtual void PrintData()const/* can make it with operator << (friend) */
    {
        std::cout<<m_data;
    }
    linkedListLeaf *GetNext()const
    {
        return (m_next);
    }

private:
    T m_data;
    linkedListLeaf *m_next;
};

template <typename T>
class linked_list:public linked_list_interface
{
public:
    linked_list(){}
    linked_List(T first): head(new linkedListLeaf(first)){}
    linked_list(linked_list &other);
    operator=(linked_list &other);
    virtual ~linked_list();

    virtual T GetData();
    virtual void SetData(T new_data);
    virtual void PrintData();
    int ForEachNode(int (*foo)(T operate_on));
    size_t CountNodes()const;
    T& FindNode(int (*cmp_foo)(T node_data, T cmp_to), T cmp_to);

private:
    linkedListLeaf *head;
};

#endif// __LINKED_LIST_HPP