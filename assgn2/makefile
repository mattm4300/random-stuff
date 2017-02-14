
FLAGS = -Wall -Wextra -std=c99

bstrees: bstrees.o bst.o scanner.o comparator.o integer.o real.o string.o
	gcc $(FLAGS) bstrees.o bst.o scanner.o comparator.o integer.o real.o string.o -o bstrees
bstrees.o: bstrees.c bst.h scanner.h comparator.h integer.h real.h string.h
	gcc $(FLAGS) -c bstrees.c
bst.o: bst.c bst.h
	gcc $(FLAGS) -c bst.c
scanner.o: scanner.c scanner.h
	gcc $(FLAGS) -c scanner.c
comparator.o: comparator.c comparator.h
	gcc $(FLAGS) -c comparator.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
real.o: real.c real.h
	gcc $(FLAGS) -c real.c
string.o:
	gcc $(FLAGS) -c string.c
cleanbuild:
	clear
	make clean
	make
clean:
	rm -f bstrees.o bst.o scanner.o comparator.o integer.o real.o string.o bstrees
