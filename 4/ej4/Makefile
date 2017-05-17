CFLAGS = -Wall -pthread -lrt
CC = gcc
OBJ = prog_a.o prog_b.o
BIN = prog_a prog_b



all: $(BIN)

clean:
	rm -f $(OBJ) $(BIN)  

prog_a: prog_a.o
	$(CC) -o prog_a prog_a.o $(CFLAGS)

prog_a.o: prog_a.c
	$(CC) -c prog_a.c -o prog_a.o $(CFLAGS)

prog_b: prog_b.o
	$(CC) -o prog_b prog_b.o $(CFLAGS)

prog_b.o: prog_b.c
	$(CC) -c prog_b.c -o prog_b.o $(CFLAGS)
