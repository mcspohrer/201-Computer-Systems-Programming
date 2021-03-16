.PHONY: clean
CFLAGS= -ansi -pedantic -O0 -Wall

all: hw3 hw3a1

hw3a1: crca1.o hw3.o
	gcc -g -o hw3a1 $(CFLAGS) hw3.o crca1.o

hw3: hw3.o crc.o
	gcc -g -o hw3 $(CFLAGS) hw3.o crc.o
	
crca1.o: crca1.s
	as --64 -o crca1.o crca1.s

hw3.o: hw3.c
	gcc -c -g -o hw3.o $(CFLAGS) hw3.c

crc.o: crc.c
	gcc -c -g -o crc.o $(CFLAGS) crc.c

clean:
	rm -f *.o hw3 hw3a1
