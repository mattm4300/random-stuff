FLAGS = -Wall -Wextra -std=c99

djikstra: djikstra.o scanner.o edgeReader.o darray.o integer.o
	gcc $(FLAGS) djikstra.o scanner.o edgeReader.o darray.o integer.o -o djikstra
djikstra.o: djikstra.c edgeReader.h integer.h darray.h
	gcc $(FLAGS) -c djikstra.c
scanner.o: scanner.c scanner.h
	gcc $(FLAGS) -c scanner.c
edgeReader.o: edgeReader.c edgeReader.h scanner.h
	gcc $(FLAGS) -c edgeReader.c
darray.o: darray.c darray.h
	gcc $(FLAGS) -c darray.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
test: djikstra
	./djikstra verts.txt
clean:
	rm -f djikstra.o scanner.o edgeReader.o darray.o integer.o
