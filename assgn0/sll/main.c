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
    printf("=======================================\n");
    if (sizeSLL(items) != 0) {
         printf("Head: %d\n", getInteger(items->head->value));
         printf("Tail: %d\n", getInteger(items->tail->value));
    }
    printf("Size: %d\n", sizeSLL(items));
    displaySLL(stdout, items);
    printf("\n");
    printf("=======================================\n");
}

static void showItems(sll *items)
      {
      printf("The items are ");
      displaySLL(stdout,items);
      printf(".\n");
      }



 int main(void)
      {
      srand(time(NULL));
     sll *a = newSLL(displayInteger);
     sll *b = newSLL(displayInteger);

     int i = 0;
     for(i = 0; i < (rand() % 10) + 2; i++) {
          int val = rand() % 100;
          //printf("Inserting %d into %d in a.\n", val, sizeSLL(a));
          insertSLL(a, sizeSLL(a), newInteger(val));
     }
     for(i = 0; i < (rand() % 10) + 2; i++) {
          int val = rand() % 100;
          //printf("Inserting %d into %d in b.\n", val, sizeSLL(b));
          insertSLL(b, sizeSLL(b), newInteger(val));
     }
     diagnose_sll(a);
     diagnose_sll(b);
     printf("\n\n joining \n\n");
     unionSLL(a, b);
     diagnose_sll(a);
     diagnose_sll(b);

      return 0;
      }
