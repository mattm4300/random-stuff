#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "dll.h"
#include "integer.h"

void
Fatal(char *fmt, ...)
    {
    va_list ap;

    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
    }

void diagnose_dll(dll *items) {
	printf("-----\n");
	if(sizeDLL(items) != 0) {
		printf("Head: %d\n", getInteger(items->head->value));
		printf("Tail: %d\n", getInteger(items->tail->value));
		printf("Head->prev.: %d\n", getInteger(items->head->previous->value));
		printf("Tail->next: %d\n", getInteger(items->tail->next->value));
	}
	printf("Size: %d\n", sizeDLL(items));
	displayDLL(stdout, items);
	printf("\n-----\n");
}

int main(void) {
	srand(time(NULL));
	dll *a = newDLL(displayInteger);
	printf("Building first list => \n");
	int amount = (rand() % 5) + 5;
	int counter = 0;
	for(counter = 0; counter < amount; ++counter) {
		insertDLL(a, 0, newInteger(rand() % 100));
	}
	printf("Displaying list: \n");
	diagnose_dll(a);
	printf("Size should be %d, size is: %d\n", amount, sizeDLL(a));

	printf("Testing insert function =>\n");
	int val = rand() % 100;

	printf("@ head with val %d: \n", val);
	insertDLL(a, 0, newInteger(val));
	diagnose_dll(a);

	val = rand() % 100;
	printf("@ tail with val %d: \n", val);
	insertDLL(a, sizeDLL(a), newInteger(val));
	diagnose_dll(a);

	val = rand() % 100;
     int index = rand() % sizeDLL(a);
     if(index == 0) {
	     ++index;
     } else if(index == sizeDLL(a)) {
	     --index;
     }
     printf("@ index %d with val %d: \n", index, val);
     insertDLL(a, index, newInteger(val));
     diagnose_dll(a);

	val = rand() % 100;
	printf("@ index just aftet head with val %d: \n", val);
	insertDLL(a, 1, newInteger(val));
	diagnose_dll(a);

	val = rand() % 100;
	printf("@ index just before tail (index %d) with val %d: \n", sizeDLL(a) - 2, val);
	insertDLL(a, sizeDLL(a) - 2, newInteger(val));
	diagnose_dll(a);

     printf("Testing remove function =>\n");

     printf("@ head: %d\n", getInteger(removeDLL(a, 0)));
     diagnose_dll(a);
     printf("@ tail: %d\n", getInteger(removeDLL(a, sizeDLL(a) - 1)));
     diagnose_dll(a);
     index = rand() % (sizeDLL(a) - 1);
     if(index == 0) {
 		++index;
     } else if(index == (sizeDLL(a) - 1)) {
		--index;
     }
     printf("@ index %d: %d\n", index, getInteger(removeDLL(a, index)));
     diagnose_dll(a);

	printf("@ index 1: %d\n", getInteger(removeDLL(a, 1)));
	diagnose_dll(a);
	printf("@ index just before the tail (index %d): %d\n", (sizeDLL(a) - 2), getInteger(removeDLL(a, (sizeDLL(a) - 2))));
	diagnose_dll(a);

     printf("Building second list => \n");
     dll *b = newDLL(displayInteger);
     amount = (rand() % 5) + 3;
     counter = 0;
     for(counter = 0; counter < amount; counter++) {
	     insertDLL(b, 0, newInteger(rand() % 100));
     }
     printf("Second list: "); displayDLL(stdout, b); printf("\n");
     printf("Size is: %d\n", sizeDLL(b));

     printf("Joining lists =>\n");
     unionDLL(a, b);
     printf("First list: \n"); diagnose_dll(a);
     printf("Second list: \n"); diagnose_dll(b);

     printf("Testing get function on first list =>\n");
     printf("List is: (should print %d items)\n", sizeDLL(a)); displayDLL(stdout, a); printf("\n");
	printf(" ");
     for(counter = 0; counter < sizeDLL(a); ++counter) {
	     printf("%d ",getInteger(getDLL(a, counter)));
     }
	printf("\n");

	return 0;
}
