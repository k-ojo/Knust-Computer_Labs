CC=gcc
CFLAGS=-g -Wall
SRC = $(wildcard *.c)
OBJ=$(SRC: .c=.o)
TARGET = main

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o main