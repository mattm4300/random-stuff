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

void printArr(int *arr, int size) {
     int index = 0;
     while(index < size) {
          printf("%d ", arr[index]);
          index++;
     }
     printf("\n");
}

int main(void) {
     srand(time(NULL));
     queue *myqueue = newQueue(displayInteger);
     int count = rand() % 15, i;
     int arr[count];
     for(i = 0; i < count; i++) {
          int val = rand() % 100;
          enqueue(myqueue, newInteger(val));
          arr[i] = val;
     }
     printf("ARR:\n");
     printArr(arr, count);
     printf("Q:\n");
     displayQueue(stdout, myqueue);
     printf("\n");

     printf("Dequeueing items:\n");
     for(i = 0; i < count; i++) {
          printf("current size: %d\n", sizeQueue(myqueue));
          printf("%d | %d\n", i, getInteger(dequeue(myqueue)));
     }
     printf("current size: %d\n", sizeQueue(myqueue));
}
