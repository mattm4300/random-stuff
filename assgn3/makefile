FLAGS = -Wall -Wextra -std=c99

dijkstra: dijkstra.o scanner.o vertex.o darray.o integer.o real.o string.o binomial.o comparator.o queue.o sll.o
	gcc $(FLAGS) scanner.o vertex.o darray.o integer.o real.o string.o binomial.o comparator.o queue.o sll.o dijkstra.o -o dijkstra
dijkstra.o: dijkstra.c vertex.h integer.h darray.h binomial.h comparator.h queue.h
	gcc $(FLAGS) -c dijkstra.c
scanner.o: scanner.c scanner.h
	gcc $(FLAGS) -c scanner.c
vertex.o: vertex.c vertex.h scanner.h integer.h darray.h binomial.h
	gcc $(FLAGS) -c vertex.c
darray.o: darray.c darray.h
	gcc $(FLAGS) -c darray.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
real.o: real.c real.h
	gcc $(FLAGS) -c real.c
string.o: string.c string.h
	gcc $(FLAGS) -c string.c
binomial.o: binomial.c binomial.h darray.h queue.h
	gcc $(FLAGS) -c binomial.c
queue.o: queue.c queue.h sll.h
	gcc $(FLAGS) -c queue.c
sll.o: sll.c sll.h
	gcc $(FLAGS) -c sll.c
comparator.o: comparator.c comparator.h integer.h real.h string.h
	gcc $(FLAGS) -c comparator.c
test: dijkstra
	./dijkstra verts.txt
build:
	clear
	make clean
	make
clean-test:
	make build
	make test
clean:
	rm -f dijkstra.o scanner.o vertex.o darray.o integer.o real.o string.o binomial.o comparator.o queue.o sll.o dijkstra
