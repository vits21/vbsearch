# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 2 of the License

# Author: Andrey Vitsenko: <avits@mail.ru>

CC=gcc
CFLAGS=-O3 -c
LD_LIB=-lm


all:	vbsearch

vbsearch:	main.o vbsearch.o
	$(CC) main.o vbsearch.o -o vbsearch $(LD_LIB)

main.o:	main.c
	$(CC) $(CFLAGS) main.c
	
vbsearch.o:	vbsearch.c
	$(CC) $(CFLAGS) vbsearch.c

clean: 
	rm -f *.o vbsearch


