default: main
	./main

compile: main.c 
	gcc -o main main.c src/*.c