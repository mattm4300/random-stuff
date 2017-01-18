FLAGS = -Wall -Wextra -std=c99

app: main.o dll.o
	gcc $(FLAGS) main.o dll.o -o app
main.o: main.c dll.h
	gcc $(FLAGS) -c main.c
dll.o: dll.c dll.h
	gcc $(FLAGS) -c dll.c
clean:
	rm main.o dll.o app
