CC= gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g
INCLUDE = /home/asafitach/asaf-itach/ds/include/
SRC = /home/asafitach/asaf-itach/ds/src/
LIB = /home/asafitach/asaf-itach/ds/lib/
TEST = /home/asafitach/asaf-itach/ds/test/
BINS = $(LIB)libscheduler.so libscheduler.o libscheduler_test.out
REQ = $(SRC)scheduler $(SRC)task $(SRC)uid $(SRC)srtlist $(SRC)pqueue $(SRC)dllist

          
all: $(BINS)

libscheduler_test.out : $(TEST)scheduler_test.o $(LIB)libscheduler.so
	$(CC) $(CFLAGS) -o $@ -L $(LIB)libscheduler.so -Wl,-rpath=$(LIB) $^ 

libscheduler.o : $(REQ) 
	$(CC) $(CFLAGS) -c -o $@ $^ -I $(INCLUDE)
	
$(LIB)libscheduler.so : $(REQ) $(INCLUDE)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ -I $(INCLUDE)

$(TEST)scheduler_test.o : $(TEST)scheduler_test.c $(INCLUDE)
	$(CC) $(CFLAGS) -c -o $@  $< -I $(INCLUDE) 

.PHONY : clean
clean :
	rm *.o $(BINS)
