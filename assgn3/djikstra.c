#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "edgeReader.h"
#include "integer.h"
#include "darray.h"

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

// Returns a square matrix filled of ints filled with -1s.
static int **newSquareMatrix(int sideLength) {
     int **mat = malloc(sizeof(int *) * sideLength);
     int index = 0;
     for(index = 0; index < sideLength; ++index) {
          mat[index] = malloc(sizeof(int) * sideLength);
     }
     int i = 0; int j = 0;
     for(i = 0; i < sideLength; i++) {
          for(j = 0; j < sideLength; j++) {
               mat[i][j] = -1;
          }
     }
     return mat;
}

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

     DArray *a = newDArray(displayInteger);
     displayDArray(stdout, a); printf("\n");
     insertDArray(a, newInteger(50));
     displayDArray(stdout, a); printf("\n");
     insertDArray(a, newInteger(124));
     displayDArray(stdout, a); printf("\n");
     insertDArray(a, newInteger(50000));
     displayDArray(stdout, a); printf("\n");
     insertDArray(a, newInteger(22));
     displayDArray(stdout, a); printf("\n");
     insertDArray(a, newInteger(222));
     displayDArray(stdout, a); printf("\n");
     removeDArray(a);
     displayDArray(stdout, a); printf("\n");
     removeDArray(a);
     displayDArray(stdout, a); printf("\n");
     removeDArray(a);
     displayDArray(stdout, a); printf("\n");
     removeDArray(a);
     displayDArray(stdout, a); printf("\n");
     removeDArray(a);
     displayDArray(stdout, a); printf("\n");
     return 0;
}
