#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <limits.h>
#include "vertex.h"
#include "integer.h"
#include "darray.h"
#include "binomial.h"
#include "comparator.h"

/* Function copied from Dr. Lusth. Some module may call this function to
   display error messages. */
void Fatal(char *fmt, ...)
    {
    va_list ap;

    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
    }


int main(int argc, char **argv) {
     if(argc < 2) {
          fprintf(stderr, "Not enough arguments.\n");
          exit(1);
     }

     FILE *fp = fopen(argv[1], "r");
     DArray *adjList = newDArray(displayInteger);
     fillAdjList(adjList, fp);
     fclose(fp);
     debugList(stdout, adjList);




     return 0;
}
