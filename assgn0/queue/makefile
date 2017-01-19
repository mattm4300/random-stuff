FLAGS = -Wall -Wextra -std=c99
app: main.o integer.o sll.o queue.o
	gcc $(FLAGS) main.o integer.o sll.o queue.o -o app
main.o: main.c integer.h queue.h
	gcc $(FLAGS) -c main.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
sll.o: sll.c sll.h
	gcc $(FLAGS) -c sll.c
queue.o: queue.c queue.h sll.h
	gcc $(FLAGS) -c queue.c
clean:
	rm -f app main.o integer.o sll.o queue.o
