#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
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

static void showStack(stack *s)
           {
           printf("The stack is ");
           displayStack(stdout,s);
           printf(".\n");
           }

int main(void) {
     stack *items = newStack(displayInteger);
       showStack(items);
       push(items,newInteger(3));
       push(items,newInteger(2));
       showStack(items);
       printf("The value ");
       displayInteger(stdout,pop(items));
       printf(" was popped.\n");
       showStack(items);
       printf("The value ");
       displayInteger(stdout, pop(items));
       printf(" was popped.\n");
       showStack(items);
       push(items, newInteger(22));
       showStack(items);
       pop(items);
       push(items, newInteger(25));
       showStack(items);
       return 0;
    return 0;
}
