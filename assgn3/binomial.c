#include <stdio.h>
#include <stdlib.h>
#include "binomial.h"

struct BinomialNode {
     void *value;
     DArray *children;
     struct BinomialNode *parent;
     void (*display)(FILE *, void *);
};

struct Binomial {
     DArray *rootlist;
     int (*compare)(void *, void *);
     void (*update)(void *,BinomialNode *);
     BinomialNode *extreme;
     int size;
     void (*display)(FILE *, void *);
};

// =============================================================================

BinomialNode *newBinomialNode(void (*display)(FILE *,void *), void *value) {
     BinomialNode *n = malloc(sizeof(BinomialNode));
     n->value = value;
     n->parent = n;
     n->children = newDArray(display);
     n->display = display;
     return n;
}

void displayBinomialNode(FILE *fp, BinomialNode *n) {
     return;
}

// =============================================================================

Binomial *newBinomial(
          void (*d)(FILE *,void *), // Display
          int (*c)(void *,void *), // Comparator
          void (*u)(void *,BinomialNode *)) { // Updater
     Binomial *b = malloc(sizeof(Binomial));
     b->display = d; // This will be something like displayInteger!
     b->compare = c;
     b->update = u;
     // [NOTE]: unsure what get's passed as display...
     b->rootlist = newDArray(d);
     b->extreme = NULL;
     b->size = 0;
     return b;
}

// Returns the degree of a node.
static int degreeBinomialNode(BinomialNode *n) {
     return sizeDArray(n->children);
}

static BinomialNode *combine(Binomial *b, BinomialNode *x, BinomialNode *y) {
     // [NOTE]: We're using a min-heap, so if x < y, y will become a child of x.
     // x < y:
     if(b->compare(x, y) < 0) {
          int i = degreeBinomialNode(y);
          // Place y in x's child array at the index i.
          setDArray(x->children, i, y);
          // Set y's parent to x.
          y->parent = x;
          return x;
     // y < x:
     } else {
          int i = degreeBinomialNode(x);
          // Place x in y's child array at index i.
          setDArray(y->children, i, x);
          // Set x's parent to y.
          x->parent = y;
          return y;
     }
}

static void consolidate(Binomial *b, BinomialNode *n) {
     // Set degree to the number of n's children.
     int degree = degreeBinomialNode(n);
     // While b's rootlist at index degree is not empty.. loop.
     while(getDArray(b->rootlist, degree) != NULL) {
          // Set n to the comboination of n and the subtree stored at the index.
          n = combine(b, n, getDArray(b->rootlist, degree));
          // Set b's slot at index degree to NULL.
          setDArray(b->rootlist, degree, NULL);
          // Increment the degree.
          ++degree;
     }
     // Degree now indexes an empty slot, so place n at index degree, growing
     // the root list if necessary (handled by DArray class).
     setDArray(b->rootlist, degree, n);
}

static void merge(Binomial *b, DArray *a) {
     int index = 0;
     // Loop through every node in the array.
     // [NOTE]: I guess we loop through from left to right?
     for(index = 0; index < sizeDArray(a); ++index) {
          BinomialNode *n = getDArray(a, index);
          n->parent = n;
          // Consolidate b and node n.
          consolidate(b, n);
     }
     // [TODO]: maybe add array freeing call here.
     // [NOTE]: By freeing, the array, I don't think he means freeing the
     // values in the array, just the array pointer itself.
     free(a);
}

BinomialNode *insertBinomial(Binomial *b, void *value) {
     // Create a new node for the value.
     BinomialNode *n = newBinomialNode(b->display, value);
     // [NOTE]: newBinomialNode sets the node's parent to itself
     // and sets children to a newDarray.

     // Consolidate b and the new node.
     consolidate(b, n);

     b->size++;
     return n;
}




// EOF
