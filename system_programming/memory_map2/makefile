CC= gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g
INCLUDE = /home/asafitach/asaf-itach/ds/include/
SRC = /home/asafitach/asaf-itach/ds/src/
LIB = /home/asafitach/asaf-itach/ds/lib/
TEST = /home/asafitach/asaf-itach/system_programming/memory_map2/
BINS = $(LIB)libdllist.so libdllist.o libdllist_test.out

          
all: $(BINS)

libdllist_test.out : $(TEST)dllist_test.o $(LIB)libdllist.so $(TEST)string.o $(TEST)mem.o
	$(CC) $(CFLAGS) -no-pie -o $@ -L $(LIB)libdllist.so -Wl,-rpath=$(LIB) $^ -ldl

libdllist.o : $(SRC)dllist.c 
	$(CC) $(CFLAGS) -c -o $@ $^ -I $(INCLUDE)
	
$(LIB)libdllist.so : libdllist.o $(INCLUDE)dllist.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $< -I $(INCLUDE)

$(TEST)dllist_test.o : $(TEST)mem_map_ex.c $(INCLUDE)dllist.h
	$(CC) $(CFLAGS) -c -o $@  $< -I $(INCLUDE) 

.PHONY : clean
clean :
	rm *.o $(BINS)
	
	
#	
#CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -fpic
#VPATH = $(PATH_S)src:$(PATH_S)include:$(PATH_S)test:$(PATH_S)obj:$(PATH_S)lib
#PATH_S = /home/asafitach/asaf-itach/ds/
#INCLUDE = -I $(PATH_S)include
#LIBDIR = $(PATH_S)lib/


#LIB_GOAL = lib$(file).so
#GOAL = $(file).out

#$(GOAL) : $(file)_test.o $(LIBDIR)lib$(file).so
#	$(CC) -L $(LIBDIR) -Wl,-rpath=$(LIBDIR) -o $@ $^

#$(LIBDIR)lib$(file).so : $(file).o
#	$(CC) -shared -o $@ $<

#$(file).o : $(file).c $(file).h
#	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

#$(file)_test.o : $(file)_test.c $(file).h
#	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

#PHONY : clean

#clean :
#    rm -f *.o *.out $(LIBDIR)*.so
