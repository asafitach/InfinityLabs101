#include <stdio.h>


int main()
{
       int *p;
       int a = 1, b = 2, c = 3;
       char *str = "abc";
       char *p_str = str;
       char ch;


       printf("%s\n", str+1);
       printf("%d\n", sizeof(str));
       printf("%s\n", p_str);
       printf("%ld\n", sizeof(*p));
        *p = a;
        p = &c;
/*         *str = 'x';
 */    
        p_str = (char*)&c + 2;
        *p_str = 67;
        printf("“%d\n”",c);/* 01000011 00000011 */

        p =  (int*)&ch;
        *p=0;

return 0;
}