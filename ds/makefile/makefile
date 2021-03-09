TARGET = a.out
OBJ = s_l_list_test1.o s_l_list.o
DEPEND = ../include/s_l_list.h
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
CFILES = ../test/s_l_list_test1.c ../src/s_l_list.c


$(TARGET) : $(OBJ)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJ) -iquote ../include/
	
$(OBJ) : $(DEPEND)
	$(CC) -c $(CFLAGS) $(CFILES) -iquote ../include/

#libfoo.a : foo.o
#	ar -rc libfoo.a foo.o

.PHONY : clean	
clean :
	rm -f $(TARGET) $(OBJ)

	

	
	

	
	
