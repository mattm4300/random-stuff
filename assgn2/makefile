
FLAGS = -Wall -Wextra -std=c99

bstrees: bstrees.o bst.o vbst.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o stringgrabber.o
	gcc $(FLAGS) bstrees.o bst.o vbst.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o stringgrabber.o -o bstrees
bstrees.o: bstrees.c bst.h vbst.h comparator.h integer.h real.h string.h stringgrabber.h
	gcc $(FLAGS) -c bstrees.c
bst.o: bst.c bst.h
	gcc $(FLAGS) -c bst.c
vbst.o: vbst.c vbst.h bst.h
	gcc $(FLAGS) -c vbst.c
scanner.o: scanner.c scanner.h
	gcc $(FLAGS) -c scanner.c
comparator.o: comparator.c comparator.h
	gcc $(FLAGS) -c comparator.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
real.o: real.c real.h
	gcc $(FLAGS) -c real.c
string.o: string.c string.h
	gcc $(FLAGS) -c string.c
sll.o: sll.c sll.h
	gcc $(FLAGS) -c sll.c
queue.o: queue.c queue.h sll.h
	gcc $(FLAGS) -c queue.c
stringgrabber.o: stringgrabber.c stringgrabber.h string.h scanner.h
	gcc $(FLAGS) -c stringgrabber.c
cleanbuild:
	clear
	make clean
	make
clean:
	rm -f bstrees.o bst.o vbst.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o stringgrabber.o bstrees
test-v:
	./bstrees -v sampleCorpus1.txt sampleCommands1.txt myOutput1.txt
	./bstrees -v sampleCorpus2.txt sampleCommands2.txt myOutput2.txt
	./bstrees -v sampleCorpus3.txt sampleCommands3.txt myOutput3.txt
	./bstrees -v sampleCorpus4.txt sampleCommands4.txt myOutput4.txt
	./bstrees -v sampleCorpus4.txt sampleCommands5.txt myOutput9.txt
	./bstrees -v corpus0.txt commands0.txt myExtraOutput1.txt
	./bstrees -v corpus1.txt commands1.txt myExtraOutput3.txt
	./bstrees -v corpus2.txt commands3.txt myExtraOutput5.txt
	./bstrees -v corpus3.txt commands5.txt myExtraOutput7.txt
	diff myOutput1.txt out1.txt
	diff myOutput2.txt out2.txt
	diff myOutput3.txt out3.txt
	diff myOutput4.txt out4.txt
	diff myOutput9.txt out9.txt
	diff myExtraOutput1.txt output1.txt
	diff myExtraOutput3.txt output3.txt
	diff myExtraOutput5.txt output5.txt
	diff myExtraOutput7.txt output7.txt
