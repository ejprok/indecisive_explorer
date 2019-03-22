default: main
	./main

compile: main.c 
	gcc -std=c99 -Wall -o main main.c src/*.c

gdb_ready: main.c 
	gcc -g -o main main.c src/*.c 

gdb_run: main
	gdb main