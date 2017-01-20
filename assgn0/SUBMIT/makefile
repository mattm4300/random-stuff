FLAGS = -Wall -Wextra -std=c99

compile: test-sll test-dll test-stack test-queue

build: clean compile

test: test-sll test-dll test-stack test-queue
	./test-sll
	./test-dll
	./test-stack
	./test-queue

clean: clean-sll clean-dll clean-stack clean-queue

test-sll: test-sll.o sll.o integer.o
	gcc $(FLAGS) test-sll.o sll.o integer.o -o test-sll
test-sll.o: test-sll.c sll.h integer.h
	gcc $(FLAGS) -c test-sll.c
sll.o: sll.c sll.h
	gcc $(FLAGS) -c sll.c
clean-sll:
	rm -f test-sll test-sll.o sll.o integer.o


test-dll: test-dll.o dll.o integer.o
	gcc $(FLAGS) test-dll.o dll.o integer.o -o test-dll
test-dll.o: test-dll.c dll.h integer.h
	gcc $(FLAGS) -c test-dll.c
dll.o: dll.c dll.h
	gcc $(FLAGS) -c dll.c
clean-dll:
	rm -f test-dll test-dll.o dll.o integer.o

test-stack: test-stack.o stack.o integer.o dll.o
	gcc $(FLAGS) test-stack.o stack.o integer.o dll.o -o test-stack
test-stack.o: test-stack.c stack.h integer.h
	gcc $(FLAGS) -c test-stack.c
stack.o: stack.c stack.h dll.h
	gcc $(FLAGS) -c stack.c
clean-stack:
	rm -f test-stack test-stack.o stack.o integer.o

test-queue: test-queue.o queue.o integer.o sll.o
	gcc $(FLAGS) test-queue.o queue.o integer.o sll.o -o test-queue
test-queue.o: test-queue.c queue.h integer.h
	gcc $(FLAGS) -c test-queue.c
queue.o: queue.c queue.h sll.h
	gcc $(FLAGS) -c queue.c
clean-queue:
	rm -f test-queue test-queue.o queue.o integer.o

integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
