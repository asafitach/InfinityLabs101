CC= gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g

objects = main.o foo.o
          

fooer : $(objects)
	$(CC) $(CFLAGS) $(objects)  -o fooer
	
main.o : foo.h

foo.o : foo.h        

.PHONY : clean
clean :
	rm fooer $(objects)
