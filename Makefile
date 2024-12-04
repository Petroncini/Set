all: avl.o main.o
	gcc avl.o main.o

avl.o:
	gcc -c avl.c

main.o:
	gcc -c main.c

clean:
	rm *.o

run: all
	./a.out

zip:
	zip zip Makefile *.h *.c
