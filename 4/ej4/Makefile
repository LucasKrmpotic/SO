CFLAGS = -Wall -pthread -lrt
CC = gcc
OBJ = obj/prog_a.o obj/prog_b.o
BIN = bin/prog_a bin/prog_b



all: $(BIN)

clean:
	rm -f $(OBJ) $(BIN)  

bin/prog_a: obj/prog_a.o
	$(CC) -o bin/prog_a obj/prog_a.o $(CFLAGS)

obj/prog_a.o: src/prog_a.c
	$(CC) -c src/prog_a.c -o obj/prog_a.o $(CFLAGS)

bin/prog_b: obj/prog_b.o
	$(CC) -o bin/prog_b obj/prog_b.o $(CFLAGS)

obj/prog_b.o: src/prog_b.c
	$(CC) -c src/prog_b.c -o obj/prog_b.o $(CFLAGS)
