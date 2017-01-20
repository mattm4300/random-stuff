#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "queue.h"
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

void diagnose_queue(queue *a) {
     printf("-----\n");
     displayQueue(stdout, a); printf("\n");
     printf("Size: %d\n", sizeQueue(a));
     printf("-----\n");
}

int main(void) {
     srand(time(NULL));
     queue *a = newQueue(displayInteger);

     int amount = (rand() % 12) + 3;
     printf("Building queue of %d items: \n", amount);

     int counter = 0;
     for(counter = 0; counter < amount; ++counter) {
          enqueue(a, newInteger(rand() % 100));
     }
     printf("Size should be %d; size is: %d\n", amount, sizeQueue(a));
     printf("Diagnosing Queue.\n");
     diagnose_queue(a);

     printf("Testing dequeue: %d\n", getInteger(dequeue(a)));
     diagnose_queue(a);

     int val = rand() % 100;
     printf("Testing enqueue of value: %d \n", val);
     enqueue(a, newInteger(val));
     diagnose_queue(a);

     printf("Dequeueing all values: \n");
     while(sizeQueue(a) != 0) {
          dequeue(a);
          displayQueue(stdout, a); printf(" Size: %d\n", sizeQueue(a));
     }
     diagnose_queue(a);

     printf("Adding 3 items to Queue: \n");
     while(sizeQueue(a) != 3) {
          enqueue(a, newInteger(rand() % 100));
          displayQueue(stdout, a); printf(" Size: %d\n", sizeQueue(a));
     }
     printf("Peeking Queue: %d\n", getInteger(peekQueue(a)));

     printf("\n\n\n");
     return 0;
}
