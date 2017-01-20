#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "stack.h"
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

void diagnose_stack(stack *a) {
     printf("-----\n");
     displayStack(stdout, a); printf("\n");
     printf("Size: %d\n", sizeStack(a));
     printf("-----\n");
}

int main(void) {
     srand(time(NULL));
     stack *a = newStack(displayInteger);

     int amount = (rand() % 12) + 3;
     printf("Building stack of %d items: \n", amount);

     int counter = 0;
     for(counter = 0; counter < amount; ++counter) {
          push(a, newInteger(rand() % 100));
     }
     printf("Size should be %d; size is: %d\n", amount, sizeStack(a));
     printf("Diagnosing stack.\n");
     diagnose_stack(a);

     printf("Testing pop: %d\n", getInteger(pop(a)));
     diagnose_stack(a);

     int val = rand() % 100;
     printf("Testing push of value: %d \n", val);
     push(a, newInteger(val));
     diagnose_stack(a);

     printf("Popping all values: \n");
     while(sizeStack(a) != 0) {
          pop(a);
          displayStack(stdout, a); printf(" Size: %d\n", sizeStack(a));
     }
     diagnose_stack(a);

     printf("Adding 3 items to stack: \n");
     while(sizeStack(a) != 3) {
          push(a, newInteger(rand() % 100));
          displayStack(stdout, a); printf(" Size: %d\n", sizeStack(a));
     }
     printf("Peeking stack: %d\n", getInteger(peekStack(a)));

     printf("\n\n\n");
     return 0;
}
