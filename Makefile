CC=gcc
CFLAGS=-c -g -Wall
TARGET=bin/

all: prepare mysh

prepare:
	mkdir -p $(TARGET)

mysh: main.o lexer.o parser.o executor.o builtins.o common.o
	$(CC) $(TARGET)main.o $(TARGET)lexer.o $(TARGET)parser.o $(TARGET)executor.o $(TARGET)builtins.o $(TARGET)common.o -o $(TARGET)mysh

main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c -o $(TARGET)main.o

lexer.o: src/lexer.c
	$(CC) $(CFLAGS) src/lexer.c -o $(TARGET)lexer.o

parser.o: src/parser.c
	$(CC) $(CFLAGS) src/parser.c -o $(TARGET)parser.o

executor.o: src/executor.c
	$(CC) $(CFLAGS) src/executor.c -o $(TARGET)executor.o

builtins.o: src/builtins.c
	$(CC) $(CFLAGS) src/builtins.c -o $(TARGET)builtins.o

common.o: src/common.c
	$(CC) $(CFLAGS) src/common.c -o $(TARGET)common.o

clean:
	rm -rf $(TARGET)*.o $(TARGET)main

