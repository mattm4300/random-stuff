FLAGS = -std=c99 -Wall -Wextra

sqsort: sqsort.o comparator.o scanner.o reader.o sll.o dll.o stack.o queue.o integer.o string.o real.o
	gcc $(FLAGS) sqsort.o comparator.o reader.o string.o real.o integer.o scanner.o sll.o dll.o stack.o queue.o -o sqsort
sqsort.o: sqsort.c comparator.h stack.h queue.h reader.h
	gcc $(FLAGS) -c sqsort.c
reader.o: reader.c reader.h scanner.h queue.h integer.h string.h real.h
	gcc $(FLAGS) -c reader.c
comparator.o: comparator.c comparator.h integer.h string.h real.h
	gcc $(FLAGS) -c comparator.c
string.o: string.c string.h
	gcc $(FLAGS) -c string.c
real.o: real.c real.h
	gcc $(FLAGS) -c real.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
scanner.o: scanner.c scanner.h
	gcc $(FLAGS) -c scanner.c
sll.o: sll.c sll.h
	gcc $(FLAGS) -c sll.c
dll.o: dll.c dll.h
	gcc $(FLAGS) -c dll.c
stack.o: stack.c dll.h
	gcc $(FLAGS) -c stack.c
queue.o: queue.c sll.h
	gcc $(FLAGS) -c queue.c
clean:
	rm -f sqsort sqsort.o comparator.o string.o real.o integer.o scanner.o sll.o dll.o stack.o queue.o reader.o

test :
	echo running sqsort on random integers with no repeats
	./sqsort -d testInteger1.txt
	echo running sqort on random integers with repeats
	./sqsort -d testInteger2.txt
	echo running sqort on homogenized integer list with two non-homogeneous embedded sequential integer
	./sqsort -d testInteger3.txt
	echo running sqort on homogenized integer list
	./sqsort -d testInteger4.txt
	echo running sqsort on reals with no repeats
	./sqsort -r testReal1.txt
	echo running sqsort on reals with repeats
	./sqsort -r testReal2.txt
	echo running sqsort on strings with no repeats
	./sqsort -s testString1.txt
	echo running sqsort on strings with repeats
	./sqsort -s testString2.txt


jakeTest:
	echo running sqsort on integer ex 1 from assigment instructions
	./sqsort -d t-int1.txt
	echo running sqsort on integer ex 2 from ass instructions
	./sqsort -d t-int2.txt
	echo running sqsort on random integers some reapeats
	./sqsort -d t-int3.txt
	echo running sqsort on all but one integer the same
	./sqsort -d t-int4.txt
	echo running sqsort on mostly the same integers
	./sqsort -d t-int5.txt
	echo running sqsort on real ex
	./sqsort -r t-real1.txt
	echo running sqsort on real all similar
	./sqsort -r t-real2.txt
	echo running sqsort on real all but 1 similar
	./sqsort -r t-real3.txt
	echo running sqsort on string ex
	./sqsort -s t-str1.txt
	echo running sqsort on string similar
	./sqsort -s t-str2.txt
	echo running sqsort on string all but 1 similar
	./sqsort -s t-str3.txt
