#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "scanner.h"
#include "darray.h"
#include "integer.h"
#include "binomial.h"

#ifndef __VERTEX_INCLUDED__
#define __VERTEX_INCLUDED__

typedef struct edgeDefinition {
     int verta;
     int vertb;
     int weight;
} edgeDefinition;

typedef struct Vertex {
     int value;
     DArray *neighbors;
     int distance;
     int steps;
     BinomialNode *bnode;
     int visited;
     struct Vertex *prev;
} Vertex;

typedef struct Neighbor {
     Vertex *vert;
     int weight;
} Neighbor;

extern int neighborWeight(DArray *, int);
extern void update(void *, BinomialNode *);
extern Vertex *findNeighborVertex(DArray *, Neighbor *);
extern edgeDefinition *readDefinition(FILE *);
extern void displayVertex(FILE *, void *);
extern Vertex *newVertex(int vert);
extern Neighbor *newNeighbor(int vert, int weight);
extern void fillAdjList(DArray *list, FILE *fp);
extern void insertVertex(DArray *list, int a, int b, int w);
extern Neighbor *neighborInList(DArray *list, int vert);
extern Vertex *vertInList(DArray *list, int vert);
extern void debugList(FILE *fp, DArray *list);
extern int compareVertex(void *, void *);
extern Vertex *getMinVertex(DArray *);

#endif
