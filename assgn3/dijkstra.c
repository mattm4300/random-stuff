#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <limits.h>
#include "edgeReader.h"
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

// Returns a square matrix filled of ints filled with INT_MAX.
static int **newSquareMatrix(int sideLength) {
     int **mat = malloc(sizeof(int *) * sideLength);
     int index = 0;
     for(index = 0; index < sideLength; ++index) {
          mat[index] = malloc(sizeof(int) * sideLength);
     }
     int i = 0; int j = 0;
     for(i = 0; i < sideLength; i++) {
          for(j = 0; j < sideLength; j++) {
               mat[i][j] = INT_MAX; // INT_MAX defined in limits.h.
          }
     }
     return mat;
}

/*
static void displaySquareMatrix(int **mat, int sideLength) {
     int i, j;
     for(i = 0; i < sideLength; i++) {
          printf("%d: ", i);
          for(j = 0; j < sideLength; j++) {
               printf("%d ", mat[i][j]);
          }
          printf("\n");
     }
}
*/

int main(int argc, char **argv) {
     if(argc < 2) {
          fprintf(stderr, "Not enough arguments.\n");
          exit(1);
     }
     printf("Reading largest vertex...");
     int sl = largestVertex(argv[1]) + 1;
     printf("Done => lv: <%d> | sl: <%d>\n", sl-1, sl);
     printf("Building square matrix...");
     int **mat = newSquareMatrix(sl);
     printf("Done.\n");
     printf("Populating matrix...");
     populateMatrix(mat, argv[1]);
     printf("Done.\n");

     Binomial *b = newBinomial(displayInteger, intComparator, NULL);
     insertBinomial(b, newInteger(4)); printf("\n");
     insertBinomial(b, newInteger(8)); printf("\n");
     insertBinomial(b, newInteger(16)); printf("\n");
     insertBinomial(b, newInteger(5)); printf("\n");
     insertBinomial(b, newInteger(1)); printf("\n");
     displayBinomial(stdout, b);


     return 0;
}
