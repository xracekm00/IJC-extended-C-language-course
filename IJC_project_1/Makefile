# @file 	Makefile
# @author 	Martin Raček, xracekm00, FIT
# @brief 	Riešenie IJC-DU1, príklad b)
# @version 	0.2
# @date 	2025-03-22
# 
# @details 	Preloženo: gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
#			Preklad mi funguje s/bez -O2 -fsanitize=address
# 
# @note 	Na školskom serveri (merlin) sa pri preklade zobrazuje varovanie
# 			"skipping incompatible /usr/local/lib/.../libc.so", ale program funguje správne.
# 			Ide pravdepodobne o problém konfigurácie servera, nie kódu.
#
# @copyright Copyright (c) 2025

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2 -fsanitize=address
LDFLAGS = -lm -fsanitize=address  #Pridanie matematickej knižnice a overenie práce s pamäťou

#Pomocka
#target: dependencies
#    activites

all: primes primes-i steg-decode

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) primes.o eratosthenes.o error.o -o primes $(LDFLAGS)

primes-i: primes.o eratosthenes-inline.o error.o
	$(CC) $(CFLAGS) primes.o eratosthenes-inline.o error.o -o primes-i $(LDFLAGS)

primes.o: primes.c bitset.h error.h
	$(CC) $(CFLAGS) -c primes.c

eratosthenes.o: eratosthenes.c bitset.h error.h
	$(CC) $(CFLAGS) -c eratosthenes.c

eratosthenes-inline.o: eratosthenes.c bitset.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-inline.o

steg-decode: eratosthenes.o ppm.o steg-decode.o error.o
	$(CC) $(CFLAGS) eratosthenes.o ppm.o steg-decode.o error.o -o steg-decode $(LDFLAGS)

steg-decode.o: steg-decode.c ppm.h error.h bitset.h
	$(CC) $(CFLAGS) -c steg-decode.c

ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) -c ppm.c

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c

run: all
	ulimit -s 65536 && ./primes 
	ulimit -s 65536 && ./primes-i
	./steg-decode du1-obrazek.ppm

clean:
	rm -f *.o primes primes-i steg-decode
