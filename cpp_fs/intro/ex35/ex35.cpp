#include <iostream> // cout
#include <typeinfo> // type

using namespace std;
/*****************************************************************************/
struct X
{
    X() {cerr << "X Ctor" << endl; throw bad_cast();}
    X(int) {cerr << "X Ctor (int)" << endl;}
    ~X() {cerr << "X Dtor" << endl;}
};

struct Y
{
    Y() {cerr << "Y Ctor" << endl;}
    ~Y() {cerr << "Y Dtor" << endl;}
};

class L
{
public:
    L(): m_x(2) {cerr << "L Ctor" << endl;}
    ~L() {cerr << "L Dtor" << endl;}
private:
    Y m_y;
    X m_x;
};

class M
{
public:
    M() {cerr << "M Ctor" << endl;}
    ~M() {cerr << "M Dtor" << endl;}
private:
    X m_x;
    Y m_y;
};

class N
{
public:
    N() {cerr << "N Ctor" << endl;}
    ~N() {cerr << "N Dtor" << endl;}
private:
    Y m_y;
    X m_x;
};

class J
{
public:
    J(): m_y(new Y), m_x(new X) 
    { 
        cerr << "J Ctor" << endl;
    }
    
    ~J() 
    {
        cerr << "J Dtor" << endl; 
        delete m_x; 
        delete m_y;
    }
private:
    Y *m_y;
    X *m_x;
};

class K
{
public:
    K() 
    {
        /* sol1 m_y(NULL), m_x(NULL) 

            try
            {
                m_y = new Y;
                m_x = new X;
            }
            catch(bad_alloc& e)
            {
                delete m_x;
                delete m_y;
                cerr << "exception cout. what: " << e.what() << endl;
            }
        */

        /* sol2 - RAII */

        /* sol 3 - bad design!
        try
        {
            m_x = new X;
        }
        catch (bad alloc&)
        {
            return;
        }

        try
        {
            m_y = new Y;
        }
        catch (bad alloc&)
        {
            delete m_y;
            return;
        }
        */

        cerr << "K Ctor" << endl; 
        m_y = new Y;
        m_x = new X;
    }
    
    ~K() 
    {
        cerr << "K Dtor" << endl; delete m_x; delete m_y;
    }
private:
    Y *m_y;
    X *m_x;
};
/********************************** driver ***********************************/
int main()
{
    try
    {
        L var1;
    }
    catch(exception& e)
    {
        cerr << "exception cout. what: " << e.what() << endl;
    }

    return 0;
}
/*****************************************************************************/