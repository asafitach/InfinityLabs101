DIR = ~/eden-atar/ds/bin/srtlist

GOAL = srtlist.out
MAIN = ~/eden-atar/ds/test/srtlist_test.c
SRC = ~/eden-atar/ds/src/srtlist.c ~/eden-atar/ds/src/dllist.c
HEAD = ~/eden-atar/ds/include   
CFILES = $(MAIN) $(SRC) 

OBJECTS = srtlist_test.o srtlist.o dllist.o
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

GOAL : $(OBJECTS)
	$(CC) -o $(GOAL) $(CFLAGS) $(OBJECTS) -iquote $(HEAD)  

$(OBJECTS) : $(HEAD) $(CFILES) 
	$(CC) -c $(CFLAGS) $(CFILES) -iquote $(HEAD)  


.PHONY : clean

clean :
	rm -f OUT $(OBJECTS)
