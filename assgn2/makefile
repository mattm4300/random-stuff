
FLAGS = -Wall -Wextra -std=c99

bstrees: bstrees.o bst.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o stringgrabber.o
	gcc $(FLAGS) bstrees.o bst.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o stringgrabber.o -o bstrees
bstrees.o: bstrees.c bst.h comparator.h integer.h real.h string.h stringgrabber.h
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
sll.o: sll.c sll.h
	gcc $(FLAGS) -c sll.c
queue.o: queue.c queue.h sll.h
	gcc $(FLAGS) -c queue.c
stringgrabber.o: stringgrabber.c stringgrabber.h string.h scanner.h
	gcc $(FLAGS) -c stringgrabber.c
cleanbuild:
	clear
	make clean
	make
clean:
	rm -f bstrees.o bst.o scanner.o comparator.o integer.o real.o string.o bstrees
