FLAGS = -Wall -Wextra -std=c99

djikstra: djikstra.o scanner.o edgeReader.o
	gcc $(FLAGS) djikstra.o scanner.o edgeReader.o -o djikstra
djikstra.o: djikstra.c edgeReader.h
	gcc $(FLAGS) -c djikstra.c
scanner.o: scanner.c scanner.h
	gcc $(FLAGS) -c scanner.c
edgeReader.o: edgeReader.c edgeReader.h scanner.h
	gcc $(FLAGS) -c edgeReader.c
clean:
	rm -f djikstra.o scanner.o edgeReader.o
