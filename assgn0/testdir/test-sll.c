#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "sll.h"
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

void diagnose_sll(sll *items) {
     printf("-----\n");
     if(sizeSLL(items) != 0) {
          printf("Head: %d\n", getInteger(items->head->value));
          printf("Tail: %d\n", getInteger(items->tail->value));
     }
     printf("Size: %d\n", sizeSLL(items));
     displaySLL(stdout, items);
     printf("\n");
     printf("-----\n");
}

int main(void) {
    srand(time(NULL));
    sll *a = newSLL(displayInteger);
    printf("Building first list => \n");
    int amount = (rand() % 5) + 3;
    int counter = 0;
    for(counter = 0; counter < amount; counter++) {
         insertSLL(a, 0, newInteger(rand() % 100));
    }
    printf("Displaying list: "); displaySLL(stdout, a); printf("\n");
    printf("Size should be %d, size is: %d\n", amount, sizeSLL(a));

    printf("Testing insert function =>\n");
    int val = rand() % 100;

    printf("@ head with val %d: \n", val);
    insertSLL(a, 0, newInteger(val));
    diagnose_sll(a);

    val = rand() % 100;
    printf("@ tail with val %d: \n", val);
    insertSLL(a, sizeSLL(a), newInteger(val));
    diagnose_sll(a);

    val = rand() % 100;
    int index = rand() % sizeSLL(a);
    if(index == 0) {
         ++index;
    } else if(index == sizeSLL(a)) {
         --index;
    }
    printf("@ index %d with val %d: \n", index, val);
    insertSLL(a, index, newInteger(val));
    diagnose_sll(a);

    printf("Testing remove function =>\n");

    printf("@ head: %d\n", getInteger(removeSLL(a, 0)));
    diagnose_sll(a);
    printf("@ tail: %d\n", getInteger(removeSLL(a, sizeSLL(a) - 1)));
    diagnose_sll(a);
    index = rand() % (sizeSLL(a) - 1);
    if(index == 0) {
         ++index;
    } else if(index == (sizeSLL(a) - 1)) {
         --index;
    }
    printf("@ index %d: %d\n", index, getInteger(removeSLL(a, index)));
    diagnose_sll(a);

    printf("Building second list => \n");
    sll *b = newSLL(displayInteger);
    amount = (rand() % 5) + 3;
    counter = 0;
    for(counter = 0; counter < amount; counter++) {
         insertSLL(b, 0, newInteger(rand() % 100));
    }
    printf("Second list: "); displaySLL(stdout, b); printf("\n");
    printf("Size is: %d\n", sizeSLL(b));

    printf("Joining lists =>\n");
    unionSLL(a, b);
    printf("First list: \n"); diagnose_sll(a);
    printf("Second list: \n"); diagnose_sll(b);

    printf("Testing get function on first list =>\n");
    printf("List is: "); displaySLL(stdout, a); printf("\n");
    for(counter = 0; counter < sizeSLL(a); ++counter) {
         printf("%d ",getInteger(getSLL(a, counter)));
    }
    printf("\n");

    return 0;
}
