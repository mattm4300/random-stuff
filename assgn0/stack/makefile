FLAGS = -std=c99 -Wall -Wextra

app: main.o integer.o stack.o dll.o
	gcc $(FLAGS) main.o integer.o stack.o dll.o -o app
main.o: main.c integer.h stack.h
	gcc $(FLAGS) -c main.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
stack.o: stack.c stack.h dll.h
	gcc $(FLAGS) -c stack.c
dll.o: dll.h dll.c
	gcc $(FLAGS) -c dll.c
clean:
	rm -f main.o integer.o stack.o dll.o app
