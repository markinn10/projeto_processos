CC = gcc
CFLAGS = -Wall -Iinclude

SRC = src/main.c src/processo.c
OBJ = bin/main.o bin/processo.o
BIN = bin/processo

all: build

build: $(OBJ)
	$(CC) -o $(BIN) $(OBJ)

bin/main.o: src/main.c include/processo.h
	$(CC) $(CFLAGS) -c src/main.c -o bin/main.o

bin/processo.o: src/processo.c include/processo.h
	$(CC) $(CFLAGS) -c src/processo.c -o bin/processo.o

clean:
	del /Q bin\*.o bin\processo.exe 2>nul || true
