#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
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
     srand(time(NULL));
     bst *mytree = newBST(displayInteger, intComparator);
     insertBST(mytree, newInteger(50));
     insertBST(mytree, newInteger(100));
     bstNode *temp = findBSTNode(mytree, newInteger(100));
     mytree->display(stdout, temp->value); printf("\n");
     return 0;
}
