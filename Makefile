CC = gcc -g

pixelflut-c: main.o pixelflut.o
	$(CC) -o pixelflut-c main.o pixelflut.o

main.o: main.c
	$(CC) -c main.c -o main.o

pixelflut.o: pixelflut.c
	$(CC) -c pixelflut.c -o pixelflut.o