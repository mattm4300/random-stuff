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
     int sl = largestVertex(argv[1]) + 1;
     int **mat = newSquareMatrix(sl);
     populateMatrix(mat, argv[1]);


     DArray *array = newDArray(displayInteger);
     insertDArray(array,newInteger(3));
     removeDArray(array);
     displayDArray(stdout,array);
     insertDArray(array,newInteger(4));
     insertDArray(array,newInteger(7));
     insertDArray(array,newInteger(2));
     displayDArray(stdout,array);
     for (int i = 0; i < 5000; i++) insertDArray(array,newInteger(7));
     for (int i = 0; i < 4999; i++) removeDArray(array);
     displayDArray(stdout,array);
     fprintf(stdout,"%d\n",getInteger(getDArray(array,0)));

     Binomial *heap = newBinomial(displayInteger,compareInteger,NULL);
     fprintf(stdout,"Inserting...\n");
     (void) insertBinomial(heap,newInteger(4));
     displayBinomial(stdout,heap);
     fprintf(stdout,"Inserting...\n");
     (void) insertBinomial(heap,newInteger(8));
     displayBinomial(stdout,heap);
     fprintf(stdout,"Inserting...\n");
     (void) insertBinomial(heap,newInteger(16));
     displayBinomial(stdout,heap);
     fprintf(stdout,"Inserting...\n");
     (void) insertBinomial(heap,newInteger(5));
     displayBinomial(stdout,heap);
     fprintf(stdout,"Inserting...\n");
     (void) insertBinomial(heap,newInteger(1));
     displayBinomial(stdout,heap);
     fprintf(stdout,"Extracting...\n");
     (void) extractBinomial(heap);
     displayBinomial(stdout,heap);
     fprintf(stdout,"Extracting...\n");
     (void) extractBinomial(heap);
     displayBinomial(stdout,heap);
     fprintf(stdout,"Extracting...\n");
     (void) extractBinomial(heap);
     displayBinomial(stdout,heap);

     return 0;
}
