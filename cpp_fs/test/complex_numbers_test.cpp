#include "complex_numbers.hpp"

using namespace ilrd;

int main()
{
    Complex x(2, 1);
    Complex x_(2, -1);
    Complex y(-4, 6);
    Complex y_(-4, -6);

    std::cout<<"x "<<x << std::endl;
    std::cout<<"y "<<y << std::endl;

    std::cout<<"x + y "<< x + y << std::endl;
    std::cout<<"y - x "<< y - x << std::endl;

    std::cout<<"x + x_ "<< x + x_ << std::endl;
    std::cout<<"y / y_ "<< y / y_ << std::endl;

    std::cout<<"x == x "<< (x == x) << std::endl;
    std::cout<<"y != y_ "<< (y != y_) << std::endl;

    std::cout<<"x + x_ "<< x + x_ << std::endl;
    for (int i = 0; i < 0xff; ++i)
    {
        x += x_;
        std::cout<<"x + x_ "<< x << std::endl;
    }


/*     Complex in;
    std::cin>>in;
    std::cout<<in; */

    return (0);
}