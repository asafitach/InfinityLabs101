#include <iostream>
#include <cstdlib>


class Counter
{
public:
	Counter(): m_counter(0)
    {}
	~Counter() 
    {}
	
    void reset()
	{
    	m_counter = 0;
	}
	unsigned int get()
	{
	    return m_counter;
	}

	void operator++()
	{
    	m_counter++;
	}

	void operator++(int)
	{
	    m_counter++;
	}

	void operator--()
	{
    	m_counter--;
	}
	void operator--(int)
	{
	m_counter--;
	}

	// Overloading << operator
    friend std::ostream& operator<<(std::ostream& os,
                               const Counter& counter)
    {
        os << "Counter Value : " << counter.m_counter
           << std::endl;
        return os;
    }

private:
	Counter(const Counter&);
	Counter& operator=(const Counter&);
	unsigned int m_counter;
};


int main()
{
    Counter ctr;
    std::cout<<ctr;
    ++ctr;
    std::cout<<ctr;
    ctr++;
    std::cout<<ctr;
    Counter *pctr = new Counter;
    (*pctr)++;
    std::cout<<*pctr;
    std::cout<<pctr<<std::endl;

    return 0;

}