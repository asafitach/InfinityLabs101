TARGET = a.out
OBJ = queue_test.o queue.o s_l_list.o
DEPEND = ../../include/queue.h ../../include/s_l_list.h
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
CFILES = ../../test/queue_test.c ../../src/queue.c ../../src/s_l_list.c


$(TARGET) : $(OBJ)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJ) -iquote ../../include/
	
$(OBJ) : $(DEPEND) $(CFILES)
	$(CC) -c $(CFLAGS) $(CFILES) -iquote ../../include/

.PHONY : clean	
clean :
	rm -f $(TARGET) $(OBJ)
