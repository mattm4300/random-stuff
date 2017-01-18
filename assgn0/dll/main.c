#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
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
    dll *mydll = newDLL(displayInteger);
    free(mydll);
    printf("done.\n");
    return 0;
}
