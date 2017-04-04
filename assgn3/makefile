FLAGS = -Wall -Wextra -std=c99 -O3

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
	./dijkstra single.0 > myOutSingle.txt
	./dijkstra two.0 > myOutTwo.txt
	./dijkstra unweighted.0 > myOutUnweighted.txt
	./dijkstra g6.0 > myOutG6.txt
	./dijkstra g7.0 > myOutG7.txt
	./dijkstra g8.0 > myOutG8.txt
	./dijkstra g9.0 > myOutG9.txt
	./dijkstra g10.0 > myOutG10.txt
	./dijkstra g11.0 > myOutG11.txt
	./dijkstra g12.0 > myOutG12.txt
	./dijkstra g13.0 > myOutG13.txt
	./dijkstra g14.0 > myOutG14.txt
	./dijkstra g15.0 > myOutG15.txt
	./dijkstra g16.0 > myOutG16.txt
	./dijkstra g17.0 > myOutG17.txt
	diff outSingle.txt myOutSingle.txt
	diff outTwo.txt myOutTwo.txt
	diff outUnweighted.txt myOutUnweighted.txt
	diff outG6.txt myOutG6.txt
	diff outG7.txt myOutG7.txt
	diff outG8.txt myOutG8.txt
	diff outG9.txt myOutG9.txt
	diff outG10.txt myOutG10.txt
	diff outG11.txt myOutG11.txt
	diff outG12.txt myOutG12.txt
	diff outG13.txt myOutG13.txt
	diff outG14.txt myOutG14.txt
	diff outG15.txt myOutG15.txt
	diff outG16.txt myOutG16.txt
	diff outG17.txt myOutG17.txt
mytest: dijkstra
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
