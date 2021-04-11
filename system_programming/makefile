CC= gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g
INCLUDE= -iquote ../include/

          
all: a.out

a.out : %o
	$(CC) $(CFLAGS) -o a.out $^ $(INCLUDE)
	
%o : %c
	$(CC) $(CFLAGS) $^ $(INCLUDE)



.PHONY : clean
clean :
	rm *.o
