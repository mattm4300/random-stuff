FLAGS = -Wall -Wextra -std=c99

all:
	make test-sll

test-sll: test-sll.c integer.o sll.o
	gcc $(FLAGS) test-sll.c integer.o sll.o -o test-sll
test-dll: test-dll.c integer.o dll.o
	gcc $(FLAGS) test-dll.c integer.o dll.o -o test-dll

integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
sll.o: sll.c sll.h
	gcc $(FLAGS) -c sll.c
dll.o: dll.c dll.h
	gcc $(FLAGS) -c dll.c	
clean:
	rm -f test-sll integer.o sll.o
