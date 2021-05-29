

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


614== Memcheck, a memory error detector
==224614== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==224614== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==224614== Command: ./a.out
==224614== 
critic begin

==224614== Syscall param rt_sigaction(act->sa_mask) points to uninitialised byte(s)
==224614==    at 0x4873496: __libc_sigaction (sigaction.c:58)
==224614==    by 0x109572: WatchDogStart (watch_dog.c:90)
==224614==    by 0x109384: main (critical_process.c:12)
==224614==  Address 0x1ffefffa88 is on thread 1's stack
==224614==  in frame #0, created by __libc_sigaction (sigaction.c:43)
==224614==  Uninitialised value was created by a stack allocation
==224614==    at 0x109524: WatchDogStart (watch_dog.c:85)
==224614== 
==224614== Syscall param rt_sigaction(act->sa_flags) points to uninitialised byte(s)
==224614==    at 0x4873496: __libc_sigaction (sigaction.c:58)
==224614==    by 0x109572: WatchDogStart (watch_dog.c:90)
==224614==    by 0x109384: main (critical_process.c:12)
==224614==  Address 0x1ffefffa78 is on thread 1's stack
==224614==  in frame #0, created by __libc_sigaction (sigaction.c:43)
==224614==  Uninitialised value was created by a stack allocation
==224614==    at 0x10951C: WatchDogStart (watch_dog.c:85)
==224614== 
pid: 224614

==224614== Thread 2:
==224614== Syscall param rt_sigaction(act->sa_mask) points to uninitialised byte(s)
==224614==    at 0x4873496: __libc_sigaction (sigaction.c:58)
==224614==    by 0x109645: InitScheduler (watch_dog_lib.c:31)
==224614==    by 0x10949C: StartUpThread (watch_dog.c:54)
==224614==    by 0x4867608: start_thread (pthread_create.c:477)
==224614==    by 0x49A3292: clone (clone.S:95)
==224614==  Address 0x5675b58 is on thread 2's stack
==224614==  in frame #0, created by __libc_sigaction (sigaction.c:43)
==224614==  Uninitialised value was created by a stack allocation
==224614==    at 0x1095D3: InitScheduler (watch_dog_lib.c:16)
==224614== 
==224614== Syscall param rt_sigaction(act->sa_flags) points to uninitialised byte(s)
==224614==    at 0x4873496: __libc_sigaction (sigaction.c:58)
==224614==    by 0x109645: InitScheduler (watch_dog_lib.c:31)
==224614==    by 0x10949C: StartUpThread (watch_dog.c:54)
==224614==    by 0x4867608: start_thread (pthread_create.c:477)
==224614==    by 0x49A3292: clone (clone.S:95)
==224614==  Address 0x5675b48 is on thread 2's stack
==224614==  in frame #0, created by __libc_sigaction (sigaction.c:43)
==224614==  Uninitialised value was created by a stack allocation
==224614==    at 0x1095D3: InitScheduler (watch_dog_lib.c:16)
==224614== 
17592186044416==224614== 
==224614== HEAP SUMMARY:
==224614==     in use at exit: 698 bytes in 13 blocks
==224614==   total heap usage: 14 allocs, 1 frees, 1,722 bytes allocated
==224614== 
==224614== Thread 1:
==224614== 272 bytes in 1 blocks are possibly lost in loss record 13 of 13
==224614==    at 0x483DD99: calloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==224614==    by 0x40149CA: allocate_dtv (dl-tls.c:286)
==224614==    by 0x40149CA: _dl_allocate_tls (dl-tls.c:532)
==224614==    by 0x4868322: allocate_stack (allocatestack.c:622)
==224614==    by 0x4868322: pthread_create@@GLIBC_2.2.5 (pthread_create.c:660)
==224614==    by 0x10940D: WdStartUp (watch_dog.c:24)
==224614==    by 0x109581: WatchDogStart (watch_dog.c:92)
==224614==    by 0x109384: main (critical_process.c:12)
==224614== 
==224614== LEAK SUMMARY:
==224614==    definitely lost: 0 bytes in 0 blocks
==224614==    indirectly lost: 0 bytes in 0 blocks
==224614==      possibly lost: 272 bytes in 1 blocks
==224614==    still reachable: 426 bytes in 12 blocks
==224614==         suppressed: 0 bytes in 0 blocks
==224614== Reachable blocks (those to which a pointer was found) are not shown.
==224614== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==224614== 
==224614== For lists of detected and suppressed errors, rerun with: -s
==224614== ERROR SUMMARY: 5 errors from 5 contexts (suppressed: 0 from 0)
