all: main.o Matrix.o
	gcc -std=c11 -c main.c -o main.o
	gcc -std=c11 -c Matrix.c -o Matrix.o
	gcc -std=c11 main.o Matrix.o -o main.out
	./main.out

main.o: main.c
	gcc -std=c11 -c main.c -o main.o

Matrix.o: Matrix.c
	gcc -std=c11 -c Matrix.c -o Matrix.o

run: 
	./main.out