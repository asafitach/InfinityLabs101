
%.o:%.c

	gcc -c $< -o $@ -I ../include





## Makefile template for a shared library in C
## https://www.topbug.net/blog/2019/10/28/makefile-template-for-a-shared-library-in-c-with-explanations/

#CC = gcc  # C compiler
#CFLAGS = -fPIC -Wall -Wextra -O2 -g  # C flags
#LDFLAGS = -shared   # linking flags
#RM = rm -f   # rm command
#TARGET_LIB = libtarget.so  # target lib

#SRCS = main.c src1.c src2.c  # source files
#OBJS = $(SRCS:.c=.o)

#.PHONY: all
#all: ${TARGET_LIB}

#$(TARGET_LIB): $(OBJS)
#	$(CC) ${LDFLAGS} -o $@ $^

#$(SRCS:.c=.d):%.d:%.c
#	$(CC) $(CFLAGS) -MM $< >$@

#include $(SRCS:.c=.d)

#.PHONY: clean
#clean:
#	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)



#CC= gcc
#CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g
#SHARED= -shered
#INCLUDE= -iquote ../include/

#          
#all: a.out
#%o : %c
#	$(CC) $(CFLAGS) $^ $(INCLUDE)

#a.out : %o
#	$(CC) $(CFLAGS) -o a.out $^ $(INCLUDE)
#	



#.PHONY : clean
#clean :
#	rm *.o






#TARGET = stack

#OBJ = $(TARGET)_test.o $(TARGET).o
#CFILES = ../test/$(TARGET)_test.c ../src/$(TARGET).c
#DEPEND = ../include/$(TARGET).h
#CC = gcc
#CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

#$(TARGET) : $(OBJ)
#	$(CC) -o a.out $(CFLAGS) $(OBJ) -iquote ../include/
#	
#$(OBJ) : $(DEPEND)
#	$(CC) -c $(CFLAGS) $(CFILES) -iquote ../include/


#.PHONY : clean	
#clean :
#	rm -f *o *out

	

	
	

	
	
