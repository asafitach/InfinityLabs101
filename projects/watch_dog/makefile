

#######################################################################################
# SUBJECT: Calculator MAKEFILE
#
# DEVELOPER: Moshe Elisha				TEAM:
#
#######################################################################################
#Variable Definitions

TDIR = ./
IDIR = ../../ds/include
SDIR = ../../ds/src
ODIR = ./
OBJS = $(ODIR)a.o 
OBJSWD = $(ODIR)watch_dog_main.o
CC = gcc -g -ansi -pedantic-errors -Wall -I $(IDIR) -I ./ -lm -pthread


##########################################################################################################

all: a.out watch_dog_main.out

##########################################################################################################
#creates an executable for avl DS
watch_dog_main.out: $(OBJSWD)
	$(CC) $(OBJS) -o $@

a.out: $(OBJS)
	$(CC) $(OBJS) -o $@

############################################################################################################
#creates object files

$(ODIR)watch_dog_main.out: ./watch_dog_main.c $(SDIR)/dllist.c $(SDIR)/task.c $(SDIR)/scheduler.c $(SDIR)/uid.c $(SDIR)/pqueue.c $(IDIR)/pqueue.h $(IDIR)/uid.h $(IDIR)/scheduler.h $(IDIR)/task.h $(IDIR)/dllist.h ./ 
	$(CC)  $(SDIR)/stack/stack.c -o $@

$(ODIR)/calculator.o: calculator.c $(IDIR)/calculator.h
	$(CC) -c calculator.c -o $@

$(ODIR)/calculator_test.o: $(TDIR)/calculator_test.c
	$(CC) -c $(TDIR)/calculator_test.c -o $@


############################################################################################################
#Utilities
.PHONY: clean all release debug test

clean:
	rm $(ODIR)/*.o *.out


	gd -o watch_dog_main.out ./watch_dog_main.c watch_dog.c ./watch_dog_lib.c ../../ds/src/dllist.c ../../ds/src/task.c ../../ds/src/uid.c  ../../ds/src/scheduler.c ../../ds/src/pqueue.c ../../ds/src/srtlist.c -I . -I ../../ds/include -pthread

	gd ./critical_process.c watch_dog.c ./watch_dog_lib.c ../../ds/src/dllist.c ../../ds/src/task.c ../../ds/src/uid.c  ../../ds/src/scheduler.c ../../ds/src/pqueue.c ../../ds/src/srtlist.c -I . -I ../../ds/include -pthread
