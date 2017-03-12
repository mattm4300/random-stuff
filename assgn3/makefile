FLAGS = -Wall -Wextra -std=c99

prog: main.o
	gcc $(FLAGS) main.o -o prog
main.o: main.c
	gcc $(FLAGS) -c main.c
clean:
	rm -f main.o prog
