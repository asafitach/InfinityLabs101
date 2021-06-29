#include <iostream>  /* namespace std */

#include "rcstring.hpp"
using namespace ilrd;

using std::endl;
using std::cout;
using std::cin;

#define RED "\033[5;91m"           /* print in red          */
#define GREEN "\033[1;38;5;47m"    /* print in green        */
#define MAGEN "\033[0;38;5;183m"   /* print in magenta      */
#define YELLOW "\033[1;38;5;220m"  /* print in light yellow */
#define CYAN "\033[0;96m"          /* print in cyan         */
#define LIGHT "\033[2;37m"         /* print in gray         */
#define PURPLE "\033[1;4;38;5;224m"/* print in purple       */
#define RESET "\033[1;0m"          /* reset print color     */

/*****************************************************************************/

#define TEST(name, actual, expected)\
                    cout << name << ": " ;(actual == expected) ? (cout << GREEN"PASS" RESET << endl)\
                    : (cout << RED "FAIL" RESET << endl)
            

#define NOT_TEST(name, actual, expected)\
                  cout << name << ": " ;(actual != expected) ? (cout << GREEN"PASS" RESET << endl)\
                    : (cout << RED "FAIL" RESET << endl)
/*****************************************************************************/

int main()
{
    ilrd::RCString str1;
    TEST("str1 len", str1.Length(), 0); 

    char temp[] = "Hello!";
    ilrd::RCString str2(temp);
    TEST("str2 len", str2.Length(), 6);  

    str1 = str2; 

    TEST("str1 = str2", (str2.CStr() == str1.CStr()), 1); 

    ilrd::RCString str3(str2);
    
    TEST("str2 = str3", (str2.CStr() == str3.CStr()), 1);

    str1[0] = 'L'; 

    cout << "should print \"Lello\" :" << str1 << endl; 

    TEST("str1 == str3", (str1 == str3), 0);
    TEST("str2 == str3", (str2 == str3), 1);

    TEST("str2 < str3", (str2 < str3), 0);
    TEST("str1 > str3", (str1 > str3), 1);

    return 0; 
}
