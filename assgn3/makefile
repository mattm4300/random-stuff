FLAGS = -Wall -Wextra -std=c99 -O3

dijkstra: dijkstra.o scanner.o edgeReader.o darray.o integer.o real.o string.o binomial.o comparator.o
	gcc $(FLAGS) dijkstra.o scanner.o edgeReader.o darray.o integer.o real.o string.o binomial.o comparator.o -o dijkstra -lm
dijkstra.o: dijkstra.c edgeReader.h integer.h darray.h binomial.h comparator.h
	gcc $(FLAGS) -c dijkstra.c
scanner.o: scanner.c scanner.h
	gcc $(FLAGS) -c scanner.c
edgeReader.o: edgeReader.c edgeReader.h scanner.h
	gcc $(FLAGS) -c edgeReader.c
darray.o: darray.c darray.h
	gcc $(FLAGS) -c darray.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
real.o: real.c real.h
	gcc $(FLAGS) -c real.c
string.o: string.c string.h
	gcc $(FLAGS) -c string.c
binomial.o: binomial.c binomial.h darray.h
	gcc $(FLAGS) -c binomial.c
comparator.o: comparator.c comparator.h integer.h real.h string.h
	gcc $(FLAGS) -c comparator.c
test: dijkstra
	./dijkstra verts.txt
build:
	clear
	make clean
	make
clean:
	rm -f dijkstra.o scanner.o edgeReader.o darray.o integer.o real.o string.o binomial.o comparator.o dijkstra
