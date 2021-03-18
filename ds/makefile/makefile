
TARGET = stack

OBJ = $(TARGET)_test.o $(TARGET).o
CFILES = ../test/$(TARGET)_test.c ../src/$(TARGET).c
DEPEND = ../include/$(TARGET).h
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

$(TARGET) : $(OBJ)
	$(CC) -o a.out $(CFLAGS) $(OBJ) -iquote ../include/
	
$(OBJ) : $(DEPEND)
	$(CC) -c $(CFLAGS) $(CFILES) -iquote ../include/


.PHONY : clean	
clean :
	rm -f *o *out

	

	
	

	
	
