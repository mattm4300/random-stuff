FLAGS = -Wall -Wextra -std=c99

app: main.o dll.o integer.o
	gcc $(FLAGS) main.o dll.o integer.o -o app
main.o: main.c dll.h integer.h
	gcc $(FLAGS) -c main.c
dll.o: dll.c dll.h
	gcc $(FLAGS) -c dll.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
clean:
	rm main.o dll.o integer.o app
