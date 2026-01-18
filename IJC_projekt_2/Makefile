# @file 	Makefile
# @author 	Martin Raček, xracekm00, FIT
# @brief 	Riešenie IJC-DU2, príklad 2)
# @version 	0.1
# @date 	2025-04-20
# 
# @details 	Preloženo: gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
#					   g++ (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
#
#			Komponenty: AMD Ryzen 7 8845HS w/ Radeon 780M Graphics 3.80 GHz 32,0 GB RAM
#
#			Preklad s -fsanitize=address nehlási žiadne chyby.
#			Testoval som program aj pomocou valgrindu (viz output):
#
#			==617== HEAP SUMMARY:
#			==617==     in use at exit: 0 bytes in 0 blocks
#			==617==   total heap usage: 77,439 allocs, 77,439 frees, 1,009,178 bytes allocated
#			==617==
#			==617== All heap blocks were freed -- no leaks are possible
#			==617==
#			==617== For lists of detected and suppressed errors, rerun with: -s
#			==617== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
#
#			==616== HEAP SUMMARY:
#			==616==     in use at exit: 0 bytes in 0 blocks
#			==616==   total heap usage: 44 allocs, 44 frees, 18,359 bytes allocated
#			==616==
#			==616== All heap blocks were freed -- no leaks are possible
#			==616==
#			==616== For lists of detected and suppressed errors, rerun with: -s
#			==616== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
#
# @note		Vysledky testu efektivity:
#		   	------------------------------------------
#		   	Efficiency test with -O0
#		   	C program (maxwordcount):
#		   	time ./maxwordcount < task2_input.txt
#		   	a       606
#		   	0.15user 
#		   	0.02system 
#		   	0:00.17elapsed 
#		   	50%CPU
#
#		   	C++ program (maxwordcount-cpp):
#		   	time ./maxwordcount-cpp < task2_input.txt
#		   	a       606
#		   	0.10user 
#		   	0.02system 
#		   	0:00.12elapsed 
#		   	45%CPU
#		   	------------------------------------------
#		   	Efficiency test with -O2
#		   	C program (maxwordcount):
#		   	time ./maxwordcount < task2_input.txt
#		   	a       606
#		   	0.08user
#		   	0.01system
#		   	0:00.09elapsed
#		   	40%CPU
#
#		   	C++ program (maxwordcount-cpp):
#		   	time ./maxwordcount-cpp < task2_input.txt
#		   	a       606
#		   	0.05user
#		   	0.01system
#		   	0:00.06elapsed
#		   	35%CPU
#		   	------------------------------------------
#
# @copyright Copyright (c) 2025

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra #-fsanitize=address -O2
LDFLAGS = #-fsanitize=address

CXX = g++
CXXFLAGS = -g -std=c++17 -pedantic -Wall -O2

# libraries and executables
LIB_O_MODULES = htab_init.o htab_size.o htab_bucket_count.o htab_find.o \
           htab_lookup_add.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o
LIB_O_MODULES_DEFAULT_HASH = $(LIB_O_MODULES) htab_hash_function.o

all: tail libhtab.a libhtab.so maxwordcount maxwordcount-dynamic

#Pomocka
#target: dependencies
#    activites

# Static library
libhtab.a: $(LIB_O_MODULES_DEFAULT_HASH)
	ar rcs $@ $^

# Dynamic/Shared library
libhtab.so: $(LIB_O_MODULES_DEFAULT_HASH)
	$(CC) -shared -o $@ $^

# Programme tail
tail: tail.o
	$(CC) $(LDFLAGS) -o tail tail.o

# Programme using static library and default hash function
maxwordcount: maxwordcount.o io.o libhtab.a
	$(CC) $(LDFLAGS) -o maxwordcount maxwordcount.o io.o libhtab.a

# Programme using dynamic/shared library and default hash function
maxwordcount-dynamic: maxwordcount.o io.o libhtab.so
	$(CC) $(LDFLAGS) -o maxwordcount-dynamic maxwordcount.o io.o -L. -lhtab

###############################################################################################

# Programme using static library and different hash function
maxwordcount-myhash: maxwordcount.o io.o libhtab.a
	$(CC) $(LDFLAGS) -o maxwordcount-myhash maxwordcount.o io.o libhtab.a -DMY_HASH_FUNCTION

# Programme using dynamic/shared library and different hash function
maxwordcount-myhash-dynamic: maxwordcount.o io.o libhtab.so
	$(CC) $(LDFLAGS) -o maxwordcount-myhash-dynamic maxwordcount.o io.o -L. -lhtab -DMY_HASH_FUNCTION

# C++ program
maxwordcount-cpp: maxwordcount-cpp.cc
	$(CXX) $(CXXFLAGS) -o maxwordcount-cpp maxwordcount-cpp.cc

###############################################################################################

# Objects
htab_init.o: htab_init.c htab.h htab_private.h
	$(CC) $(CFLAGS) -fPIC -c htab_init.c -o htab_init.o

htab_size.o: htab_size.c htab.h htab_private.h
	$(CC) $(CFLAGS) -fPIC -c htab_size.c -o htab_size.o

htab_bucket_count.o: htab_bucket_count.c htab.h htab_private.h
	$(CC) $(CFLAGS) -fPIC -c htab_bucket_count.c -o htab_bucket_count.o

htab_find.o: htab_find.c htab.h htab_private.h
	$(CC) $(CFLAGS) -fPIC -c htab_find.c -o htab_find.o

htab_lookup_add.o: htab_lookup_add.c htab.h htab_private.h
	$(CC) $(CFLAGS) -fPIC -c htab_lookup_add.c -o htab_lookup_add.o

htab_erase.o: htab_erase.c htab.h htab_private.h
	$(CC) $(CFLAGS) -fPIC -c htab_erase.c -o htab_erase.o

htab_for_each.o: htab_for_each.c htab.h htab_private.h
	$(CC) $(CFLAGS) -fPIC -c htab_for_each.c -o htab_for_each.o

htab_clear.o: htab_clear.c htab.h htab_private.h
	$(CC) $(CFLAGS) -fPIC -c htab_clear.c -o htab_clear.o

htab_free.o: htab_free.c htab.h htab_private.h
	$(CC) $(CFLAGS) -fPIC -c htab_free.c -o htab_free.o

htab_hash_function.o: htab_hash_function.c htab.h htab_private.h
	$(CC) $(CFLAGS) -fPIC -c htab_hash_function.c -o htab_hash_function.o

maxwordcount.o: maxwordcount.c htab.h
	$(CC) $(CFLAGS) -c maxwordcount.c -o maxwordcount.o

io.o: io.c
	$(CC) $(CFLAGS) -c io.c -o io.o

tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c -o tail.o

# Clean up
clean:
	rm -f *.o tail maxwordcount maxwordcount-dynamic maxwordcount-myhash maxwordcount-myhash-dynamic maxwordcount-cpp libhtab.a libhtab.so

# Run all versions for testing
run: all maxwordcount-myhash maxwordcount-myhash-dynamic maxwordcount-cpp
	./tail -n 28 < task1_input.txt
	./maxwordcount < task2_input.txt
	LD_LIBRARY_PATH=. ./maxwordcount-dynamic < task2_input.txt
	./maxwordcount-myhash < task2_input.txt
	LD_LIBRARY_PATH=. ./maxwordcount-myhash-dynamic < task2_input.txt
	./maxwordcount-cpp < task2_input.txt

# Check just like the assignment said
check: all
	./tail < task1_input.txt
	./maxwordcount < task2_input.txt
	LD_LIBRARY_PATH=. ./maxwordcount-dynamic < task2_input.txt
