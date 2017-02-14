#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "bst.h"
#include "scanner.h"
#include "comparator.h"
#include "string.h"
#include "real.h"
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
     bst *mytree = newBST(displayString, stringComparator);

     displayString(stdout, insertBST(mytree, newString("test"))->value);
     printf("\n");
     return 0;
}
