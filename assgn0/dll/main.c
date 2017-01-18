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
    for(i = 0; i < 100; i++) {
         printf("%d ", arr[i]);
    }
    printf("=================================================\n");
    dllnode *spot = mydll->head;
    for(i = 0; i < 100; i++) {
         printf("%d ", getInteger((integer *) spot->value));
         spot = spot->next;
    }
    return 0;
}
