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

BinomialNode *newBinomialNode(void (*display)(FILE *,void *), void *value) {
     BinomialNode *n = malloc(sizeof(BinomialNode));
     n->value = value;
     n->parent = n;
     n->children = newDArray(display);
     n->display = display;
     return n;
}

void displayBinomialNode(FILE *fp,void *n) {
     BinomialNode *x = (BinomialNode *) n; // "Unbox" the value.
     x->display(fp, x->value);
     fprintf(fp, "-N"); // Add order sometime.
     x->display(fp )
}

Binomial *newBinomial(
          void (*d)(FILE *,void *), // Display
          int (*c)(void *,void *), // Comparator
          void (*u)(void *,BinomialNode *)) { // Updater
     Binomial *b = malloc(sizeof(Binomial));
     b->display = d; // This will be something like displayInteger!
     b->compare = c;
     b->update = u;
     b->rootlist = newDArray(displayBinomialNode); // I think this is right!
     b->extreme = NULL;
     b->size = 0;
     return b;
}

BinomialNode *insertBinomial(Binomial *b, void *value) {
     BinomialNode *n = newBinomialNode(value, b->display);

}

int sizeBinomial(Binomial *b) { return b->size; }
