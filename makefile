default: main
	./main

compile: main.c 
	gcc -std=c99 -Wall -o main main.c src/*.c

fast: main.c
	gcc -O3 -std=c99 -Wall -o main main.c src/*.c

gdb_ready: main.c 
	gcc -g -o main main.c src/*.c 

gdb_run: main
	gdb main
