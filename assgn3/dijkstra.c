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
#include "queue.h"

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

static void sortVertsForPrint(DArray *arr) {
     printf("STARTING THE SORT:");
     printf("Sorting...\n");
     // Sort by weight, smallest to largest.
     // [NOTE]: ties are broken in favor of the smaller destination vertex.
     int i = 0;
     int j = 0;
     int size = sizeDArray(arr);

     for(j = 1; j < size; j++) {
          printf("a\n");
          int swapped = 0;
          for(i = 0; i < size - j; i++) {
               printf("b\n");
               Vertex *a = getDArray(arr, i);
               Vertex *b = getDArray(arr, i + 1);
               printf("Got verts.\n");
               printf("a: %d | prev: %d\n", a->value, a->prev->value);
               printf("b: %d | prev: %d\n", b->value, b->prev->value);
               Neighbor *an = neighborInList(a->neighbors, a->prev->value);
               Neighbor *bn = neighborInList(b->neighbors, b->prev->value);
               printf("Got neighbors.\n");
               printf("Neighbor a weight: %d\n", an->weight);
               printf("Neighbor b weight: %d\n", bn->weight);
               if(an->weight > bn->weight) {
                    printf("Swap need for case 1.\n");
                    setDArray(arr, i, b);
                    setDArray(arr, i + 1, a);
                    swapped = 1;
               // Tie case.
               } else if(an->weight == bn->weight) {
                    if(b->value < a->value) {
                         printf("Swap needed for tie.\n");
                         setDArray(arr, i, b);
                         setDArray(arr, i + 1, a);
                    }
               }
          }
          if(!swapped) break;
     }
     printf("Done.\n");
}

static void displayTree(FILE *fp, DArray *arr, int maxSteps) {
     printf("DISPLAY TIME NOW: \n");
     sortVertsForPrint(arr);
     int index = 0;
     for(index = 0; index < maxSteps; index++) {

     }
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
     //debugList(stdout, adjList);

     Vertex *min = getMinVertex(adjList);
     // Set the starting vertex's distance to 0 (it'll be the most)
     // extreme value in the heap.
     min->distance = 0;

     // Make a new heap.
     Binomial *heap = newBinomial(displayVertex, compareVertex, update);


     printf("Filling heap.\n");
     // Populate the heap with the vertices.
     int index = 0;
     for(index = 0; index < sizeDArray(adjList); index++) {
          Vertex *v = getDArray(adjList, index);
          v->bnode = insertBinomial(heap, v);
     }

     displayBinomial(stdout, heap);

     printf("Looping.\n");


     DArray *vertsVisited = newDArray(displayVertex);
     int maxSteps = 0;
     while(sizeBinomial(heap) != 0) {
          printf("%d\n", maxSteps);
          // Get a vertex.
          Vertex *u = extractBinomial(heap);
          printf("Vert: "); displayVertex(stdout, u); printf("\n");
          if(u->prev == NULL) {
               printf("Going to print: \n");
               displayTree(stdout, vertsVisited, maxSteps);
               vertsVisited = newDArray(displayVertex);
               u->distance = 0;
               u->steps = 0;
               maxSteps = 0;
          }

          // Loop through that vertex's neighbors.
          int j = 0;
          for(j = 0; j < sizeDArray(u->neighbors); j++) {
               Neighbor *n = getDArray(u->neighbors, j);
               Vertex *v = findNeighborVertex(adjList, n);
               if(u->distance + n->weight < v->distance) {
                    v->distance = u->distance + n->weight;
                    v->prev = u;
                    decreaseKeyBinomial(heap, v->bnode, v);
                    v->steps = v->prev->steps + 1;
                    if(v->steps > maxSteps) maxSteps = v->steps;
               }
          }
          printf("Inserting => vert: %d | prev vert: %d\n", u->value, u->prev->value);
          insertDArray(vertsVisited, u);
     }
     // Make sure to print the final tree!!!
     displayTree(stdout, vertsVisited, maxSteps);
     printf("DONE.\n");
     return 0;
}
