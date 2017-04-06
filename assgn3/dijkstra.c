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

static void displayTree(FILE *fp, queue *visited) {
     if(sizeQueue(visited) == 0) return;

     Binomial *b = newBinomial(displayVertex, compareVertex, update);
     int s = sizeQueue(visited);
     int maxSteps = 0;

     // Put all of the vertices into a heap.
     int i = 0;
     for(i = 0; i < s; i++) {
          Vertex *v =  (Vertex *) dequeue(visited);
          if(v->steps > maxSteps) maxSteps = v->steps;
          insertBinomial(b, v);
     }

     // Put each level into its own queue.
     queue *level[maxSteps];
     for(i = 0; i <= maxSteps; i++) {
          level[i] = newQueue(displayVertex);
     }

     // Put each vertex from the heap into its corresponding queue in level.
     // Since we put the vertices in the min-heap, they're inserted into the
     // queues in the correct print order.
     for(i = 0; i < s; i++) {
          Vertex *v = (Vertex *) extractBinomial(b);
          enqueue(level[v->steps], v);
     }

     // For each level, go through and print out the queues.
     for(i = 0; i <= maxSteps; i++) {
          fprintf(fp, "%d : ", i);
          while(sizeQueue(level[i]) != 0) {
               Vertex *v = (Vertex *) dequeue(level[i]);
               displayVertex(stdout, v);
               if(sizeQueue(level[i]) > 0) fprintf(fp, " ");
          }
          fprintf(fp, "\n");
     }
     fprintf(fp, "----\n");
}

static void dijkstra(FILE *fp, DArray *adjList, Binomial *heap) {
     queue *visited = newQueue(displayVertex);
     Vertex *min = getMinVertex(adjList);
     min->distance = 0;
     min->prev = min;
     min->steps =  0;
     while(sizeBinomial(heap) != 0) {
          Vertex *u = (Vertex *) extractBinomial(heap);
          // If we hit the end of a tree in the forest, print the tree then
          // continue as normal.
          if(u->prev == NULL) {
               u->distance = 0;
               displayTree(fp, visited);
               visited = newQueue(displayVertex);
          }
          enqueue(visited, u);
          u->visited = 1;
          int i = 0;
          for(i = 0; i < sizeDArray(u->neighbors); i++) {
               Neighbor *n = (Neighbor *) getDArray(u->neighbors, i);
               Vertex *v = findNeighborVertex(adjList, n);
               if(v->visited != 1) {
                    int distance = u->distance + n->weight;
                    if(distance < v->distance) {
                         v->prev = u;
                         v->distance = distance;
                         v->steps = v->prev->steps + 1;
                         decreaseKeyBinomial(heap, v->bnode, v);
                    }
               }
          }
     }
     // Make sure to print out the final tree after the alg. is done.
     displayTree(fp, visited);
}

int main(int argc, char **argv) {
     if(argc < 2) {
          fprintf(stderr, "Not enough arguments.\n");
          exit(1);
     }

     // Read the vertices from the given file into and adjacency list.
     FILE *fp = fopen(argv[1], "r");
     DArray *adjList = newDArray(displayVertex);
     fillAdjList(adjList, fp);
     // Make sure to close that file!
     fclose(fp);


     // Make a new heap.
     Binomial *heap = newBinomial(displayVertex, compareVertex, update);

     // Populate the heap with the vertices from the adjacency list.
     int index = 0;
     for(index = 0; index < sizeDArray(adjList); index++) {
          Vertex *v = getDArray(adjList, index);
          v->bnode = insertBinomial(heap, v);
     }

     //displayBinomial(stdout, heap);


     // Run dijkstra's algorithm on the heap.
     dijkstra(stdout, adjList, heap);

     return 0;
}
