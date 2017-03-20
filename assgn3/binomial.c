#include "binomial.h"

typedef struct BinomialNode {
     void *value;
     DArray *children;
     struct BinomialNode *parent;
     void (*display)(FILE *, void *);
} BinomialNode;

typedef struct Binomial {
     DArray *rootlist;
     int (*compare)(void *, void *);
     void (*update)(void *,BinomialNode *);
     BinomialNode *extreme;
     int size;
     void (*display)(FILE *, void *);
} Binomial;

Binomial *newBinomial(
          void (*d)(FILE *,void *), // Display
          int (*c)(void *,void *), // Comparator
          void (*u)(void *,BinomialNode *)) { // Updater
     Binomial *b = malloc(sizeof(Binomial));
     b->display = d;
     b->compare = c;
     b->update = u;
     b->rootlist = newDArray(d);
     b->extreme = NULL;
     b->size = 0;
     return b;
}

int sizeBinomial(Binomial *b) { return b->size; }
