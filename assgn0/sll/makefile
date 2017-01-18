FLAGS = -Wall -Wextra -std=c99
app: main.o sll.o integer.o
	gcc $(FLAGS) main.o sll.o integer.o -o app
main.o: main.c sll.h integer.h
	gcc $(FLAGS) -c main.c
sll.o: sll.c sll.h integer.h
	gcc $(FLAGS) -c sll.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
clean:
	rm main.o sll.o app integer.o
