

#include <iostream>
/*****************************************************************************/
struct X
{
/*     explicit X(); //initialization function without parameters is named 
    // default constructor (often abbreviated as: ctor)
    ~X(); // deinitialization function is called destructor (Dtor)
    X(const X& other_); //copy initialization function is called copy constructor or ctor

    X& operator=(const X& other_);// assignment operator;
 */
    explicit X(int a_, int b_ = 0); //regular (non default) ctor
    int m_a;
    //const int m_b;
    int s;
};

//why the X::x? the code after the colon is called initialization list
/* X::X(): m_a(3), m_b(4) //implementation of the default Ctor.
{
    //m_a = 3;
    //m_b = 4;
        m_a = 5;
    std::cout<< "this:" << this << " X default Ctor. m_a: " << m_a <<
                                   " m_b: " << m_b << std::endl; 
} */

X::X(int a_, int b_): m_a(a_), s(b_) //implementation of the second Ctor
{
    std::cout<< "this:" << this << " X int int Ctor. m_a: " << m_a <<
                                   " m_b: " << s << std::endl; 
}

/* 
X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b)  //implementation of the copy Ctor
{
    std::cout<< "this:" << this << " X copy Ctor. m_a: " << m_a <<
                                   " m_b: " << m_b << std::endl; 
} */


/* X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    // m_b = other_.m_b;

    std::cout<< "this:" << this << " X assignment operator. m_a: " << m_a <<
                                   " does not change m_b " << m_b << std::endl;

    return *this;
}


X::~X()
{
    std::cout<< "this:" << this << "X Dtor. m_a: " << m_a <<
                                   "m_b:" << m_b << std::endl; 
} */
/*****************************************************************************/
/* struct Y
{
    X m_x;
    int m_i;
}; */
/*****************************************************************************/
void foo()
{
    
}

int main()
{
    
    int s = 3;
    X x1; // calls default constructor
    //X x2(7); // calls constructor
    X *px = new X(x1); // calls copy constructor
	//X x3(9, 10); // calls constructor
    X x4(x1); // calls copy constructor

    //std::cout<<&s<<"\n "<< &x1<<"\n "<<&x2<< "\n "<<&px<< "\n "<<&x3<<"\n "<<&x4<<"\n\n";
	
    std::cout<<"size of struct with 2 ints "<<sizeof(X)<<std::endl;
	// X *xp = new X[];
    X *dp = new X[10];
    
    delete[] dp; dp = 0;
/* 
    x1 = x3; // calls assignment operator

    std::cout << "size of X struct is: " << sizeof(X) << std::endl;

    delete px; px = 0; // calls destructor
	//delete[] xp; xp = 0;

     Y y1 = {X(250, 750)};
 // y1.m_x.m_a = 250;
    //y1.m_x.m_b = 750;

    Y y2(y1);
    Y y3 = y1;

     //y3.m_x.m_a = y1.m_x.m_a;
/*    y3.m_x.m_b = y1.m_x.m_b; */

     
    return 0;
}
/*****************************************************************************/