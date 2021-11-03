pixelflut-c: main.o
	gcc -o pixelflut-c main.o

main.o: main.c
	gcc -c main.c -o main.o