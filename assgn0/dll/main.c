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

int main(void) {
     srand(time(NULL));
    dll *mydll = newDLL(displayInteger);
    int arr[100];
    int i;
    for(i = 0; i< 100; i++) {
         int val = rand() % 100;
         arr[i] = val;
         insertDLL(mydll, i, newInteger(val));
    }
    dllnode *spot = mydll->head;
    printf("Frontwards:\n\n");
    for(i = 0; i < 100; i++) {
         printf("%d | %d\n", arr[i], getInteger((integer *) spot->value));
         spot = spot->next;
    }
    printf("Head wrap-around: %d | %d\n", arr[0], getInteger((integer *) spot->value));
    spot = mydll->tail;
    printf("\n\nBackwards:\n\n");
    for(i = 99; i >= 0; i--) {
         printf("%d | %d\n", arr[i], getInteger((integer *) spot->value));
         spot = spot->previous;
    }
    printf("Tail wrap-around: %d | %d\n", arr[99], getInteger((integer *) spot->value));

    printf("\n\n");

    printf("h->");
    spot = mydll->head;
    int counter = 0;
    while(counter < mydll->size - 1) {
         printf("[%d]=", getInteger((integer *) spot->value));
         spot = spot->next;
         ++counter;
    }
    printf("[%d]", getInteger(spot->value));
    printf("<-t\n");

    showItems(mydll);

    return 0;
}
