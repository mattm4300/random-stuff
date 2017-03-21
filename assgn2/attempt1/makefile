
FLAGS = -Wall -Wextra -std=c99

bstrees: bstrees.o bst.o vbst.o rbt.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o stringgrabber.o
	gcc $(FLAGS) bstrees.o bst.o vbst.o rbt.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o stringgrabber.o -o bstrees
bstrees.o: bstrees.c bst.h vbst.h comparator.h integer.h real.h string.h stringgrabber.h
	gcc $(FLAGS) -c bstrees.c
bst.o: bst.c bst.h
	gcc $(FLAGS) -c bst.c
vbst.o: vbst.c vbst.h bst.h
	gcc $(FLAGS) -c vbst.c
rbt.o: rbt.c rbt.h bst.h
	gcc $(FLAGS) -c rbt.c
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
	rm -f bstrees.o bst.o vbst.o rbt.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o stringgrabber.o bstrees
test: dtest ltest btest
dtest: bstrees
	./bstrees -v sampleCorpus1.txt sampleCommands1.txt myOutput1.txt
	./bstrees -v sampleCorpus2.txt sampleCommands2.txt myOutput2.txt
	./bstrees -v sampleCorpus3.txt sampleCommands3.txt myOutput3.txt
	./bstrees -v sampleCorpus4.txt sampleCommands4.txt myOutput4.txt
	./bstrees -v sampleCorpus4.txt sampleCommands5.txt myOutput9.txt
	./bstrees -r sampleCorpus1.txt sampleCommands1.txt myOutput5.txt
	./bstrees -r sampleCorpus2.txt sampleCommands2.txt myOutput6.txt
	./bstrees -r sampleCorpus3.txt sampleCommands3.txt myOutput7.txt
	./bstrees -r sampleCorpus4.txt sampleCommands4.txt myOutput8.txt
	./bstrees -v corpus0.txt commands0.txt myExtraOutput1.txt
	./bstrees -r corpus0.txt commands0.txt myExtraOutput2.txt
	./bstrees -v corpus1.txt commands1.txt myExtraOutput3.txt
	./bstrees -r corpus1.txt commands2.txt myExtraOutput4.txt
	./bstrees -v corpus2.txt commands3.txt myExtraOutput5.txt
	./bstrees -r corpus2.txt commands4.txt myExtraOutput6.txt
	./bstrees -v corpus3.txt commands5.txt myExtraOutput7.txt
	./bstrees -r corpus3.txt commands5.txt myExtraOutput8.txt
	diff myOutput1.txt out1.txt
	diff myOutput3.txt out3.txt
	diff myOutput4.txt out4.txt
	diff myOutput5.txt out5.txt
	diff myOutput6.txt out6.txt
	diff myOutput8.txt out8.txt
	diff myExtraOutput1.txt output1.txt
	diff myExtraOutput2.txt output2.txt
	diff myExtraOutput3.txt output3.txt
	diff myExtraOutput4.txt output4.txt
	diff myExtraOutput5.txt output5.txt
	diff myExtraOutput6.txt output6.txt
	diff myExtraOutput7.txt output7.txt
	diff myExtraOutput8.txt output8.txt
ltest: bstrees
	./bstrees -v clean.0 display meout3.txt
	./bstrees -r clean.0 display meout4.txt
	./bstrees -v spaces.0 display meout5.txt
	./bstrees -r spaces.0 display meout6.txt
	./bstrees -v empty commands.0 meout7.txt
	./bstrees -r empty commands.0 meout8.txt
	./bstrees -v s9.0 display meout9.txt
	./bstrees -v w17.0 display meout17.txt
	./bstrees -r w18.0 display meout18.txt
	./bstrees -v w19.0 display meout19.txt
	./bstrees -v w21.0 display meout21.txt
	./bstrees -v w23.0 display meout23.txt
	./bstrees -r w24.0 display meout24.txt

	diff meout3.txt eout3.txt
	diff meout4.txt eout4.txt
	diff meout5.txt eout5.txt
	diff meout6.txt eout6.txt
	diff meout7.txt eout7.txt
	diff meout8.txt eout8.txt
	diff meout9.txt eout9.txt
	diff meout17.txt eout17.txt
	diff meout18.txt eout18.txt
	diff meout19.txt eout19.txt
	diff meout21.txt eout21.txt
	diff meout23.txt eout23.txt
	diff meout24.txt eout24.txt

btest: bstrees
	./bstrees -v clean.0 display btest3.txt
	./bstrees -r clean.0 display btest4.txt
	./bstrees -v spaces.0 display btest5.txt
	./bstrees -r spaces.0 display btest6.txt
	./bstrees -v empty commands.0 btest7.txt
	./bstrees -r empty commands.0 btest8.txt
	./bstrees -v s9.0 display btest9.txt
	./bstrees -r s10.0 display btest10.txt
	./bstrees -v s11.0 display btest11.txt
	./bstrees -r s12.0 display btest12.txt
	./bstrees -v s13.0 display btest13.txt
	./bstrees -r s14.0 display btest14.txt
	./bstrees -v s15.0 display btest15.txt
	./bstrees -r w16.0 display btest16.txt
	./bstrees -v w17.0 display btest17.txt
	./bstrees -r w18.0 display btest18.txt
	./bstrees -v w19.0 display btest19.txt
	./bstrees -r w20.0 display btest20.txt
	./bstrees -v w21.0 display btest21.txt
	./bstrees -r w22.0 display btest22.txt
	./bstrees -v w23.0 display btest23.txt
	./bstrees -r w24.0 display btest24.txt
	./bstrees -v clean.0 c25.0 btest25.txt
	./bstrees -r clean.0 c26.0 btest26.txt
	./bstrees -v clean.0 c27.0 btest27.txt
	./bstrees -r clean.0 c28.0 btest28.txt
	./bstrees -v clean.0 c29.0 btest29.txt
	./bstrees -r clean.0 c30.0 btest30.txt
	./bstrees -v clean.0 c31.0 btest31.txt
	./bstrees -r clean.0 c32.0 btest32.txt
	@echo dun dun dunnnnn
	./bstrees -r shakespeare.txt shakespeare.display btest33.txt
	@echo dun dun dunnnnn
	./bstrees -r beowulf.txt display btest34.txt
	./bstrees -r clean.0 c35.0 btest35.txt
	@echo Test 36 runs alternate code in graded version
	./bstrees -v clean.0 c36.0 btest36.txt
	./bstrees -v clean.0 c37.0 btest37.txt
	#Testing against existing files
	diff btest3.txt test3.txt
	diff btest4.txt test4.txt
	diff btest5.txt test5.txt
	diff btest6.txt test6.txt
	diff btest7.txt test7.txt
	diff btest8.txt test8.txt
	diff btest9.txt test9.txt
	diff btest10.txt test10.txt
	diff btest11.txt test11.txt
	diff btest12.txt test12.txt
	diff btest13.txt test13.txt
	diff btest14.txt test14.txt
	diff btest15.txt test15.txt
	diff btest16.txt test16.txt
	diff btest17.txt test17.txt
	diff btest18.txt test18.txt
	diff btest19.txt test19.txt
	diff btest20.txt test20.txt
	diff btest21.txt test21.txt
	diff btest22.txt test22.txt
	diff btest23.txt test23.txt
	diff btest24.txt test24.txt
	diff btest25.txt test25.txt
	diff btest26.txt test26.txt
	diff btest27.txt test27.txt
	diff btest28.txt test28.txt
	diff btest29.txt test29.txt
	diff btest30.txt test30.txt
	diff btest31.txt test31.txt
	diff btest32.txt test32.txt
	diff btest33.txt test33.txt
	diff btest34.txt test34.txt
	diff btest35.txt test35.txt
	diff btest36.txt test36.txt
	diff btest37.txt test37.txt
	@echo Testing Sequence complete.
