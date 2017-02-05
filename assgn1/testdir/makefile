FLAGS = -std=c99 -Wall -Wextra



sqsort: sqsort.o comparator.o scanner.o reader.o sll.o dll.o stack.o queue.o integer.o string.o real.o
	gcc $(FLAGS) sqsort.o comparator.o reader.o string.o real.o integer.o scanner.o sll.o dll.o stack.o queue.o -o sqsort
sqsort.o: sqsort.c comparator.h stack.h queue.h reader.h
	gcc $(FLAGS) -c sqsort.c
reader.o: reader.c reader.h scanner.h queue.h integer.h string.h real.h
	gcc $(FLAGS) -c reader.c
comparator.o: comparator.c comparator.h integer.h string.h real.h
	gcc $(FLAGS) -c comparator.c
string.o: string.c string.h
	gcc $(FLAGS) -c string.c
real.o: real.c real.h
	gcc $(FLAGS) -c real.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
scanner.o: scanner.c scanner.h
	gcc $(FLAGS) -c scanner.c
sll.o: sll.c sll.h
	gcc $(FLAGS) -c sll.c
dll.o: dll.c dll.h
	gcc $(FLAGS) -c dll.c
stack.o: stack.c dll.h
	gcc $(FLAGS) -c stack.c
queue.o: queue.c sll.h
	gcc $(FLAGS) -c queue.c
clean:
	rm -f sqsort sqsort.o comparator.o string.o real.o integer.o scanner.o sll.o dll.o stack.o queue.o reader.o
