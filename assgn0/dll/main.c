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

static void showItems(dll *items) {
     printf("The items are ");
     displayDLL(stdout, items);
     printf(".\n");
}

void diagnose_dll(dll *items) {
     printf("=============\n");
     if(sizeDLL(items) != 0) {
          printf("Head: %d\n", getInteger(items->head->value));
          printf("Tail: %d\n", getInteger(items->tail->value));
          printf("Head->prev.: %d\n", getInteger(items->head->previous->value));
          printf("Tail->next: %d\n", getInteger(items->tail->next->value));
     }
     printf("Size: %d\n", sizeDLL(items));
     displayDLL(stdout, items);
     printf("\n=================\n");
}

int main(void) {
     srand(time(NULL));

    dll *a = newDLL(displayInteger);
    dll *b = newDLL(displayInteger);

    int i = 0;
    for (i = 0; i < (rand() % 10) + 2; i++) {
         int val = rand() % 100;
         insertDLL(a, sizeDLL(a), newInteger(val));
    }
    for (i = 0; i < (rand() % 10) + 2; i++) {
         int val = rand() % 100;
         insertDLL(b, sizeDLL(b), newInteger(val));
    }
    diagnose_dll(a);
    diagnose_dll(b);
    printf("\njoining\n");
    unionDLL(a, b);
    diagnose_dll(a);
    diagnose_dll(b);

    return 0;
}
