CC := gcc -Wall -pedantic-errors

.PHONY: all
all: box

box: box.c cli_box.o levens.o string24k.o
	$(CC) box.c *.o -o box

cli_box.o: cli_box.c cli_box.h
	$(CC) -c cli_box.c

levens.o: levens.c levens.h
	$(CC) -c levens.c

string24k.o: string24k.c string24k.h
	$(CC) -c string24k.c

.PHONY: clean
clean:
	rm *.o

