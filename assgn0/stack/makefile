FLAGS = -std=c99 -Wall -Wextra

app: main.o integer.o stack.o sll.o
	gcc $(FLAGS) main.o integer.o stack.o sll.o -o app
main.o: main.c integer.h stack.h
	gcc $(FLAGS) -c main.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
stack.o: stack.c stack.h sll.h
	gcc $(FLAGS) -c stack.c
sll.o: sll.h sll.c
	gcc $(FLAGS) -c sll.c
clean:
	rm main.o integer.o stack.o sll.o app
