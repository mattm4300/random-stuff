#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
     // [NOTE]: unsure what getss passed as display...
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
     if(b->compare(x->value, y->value) < 0) {
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

     // [NOTE]: "The most extreme value is updated after the consolidation
     // routine runs."
     if(b->extreme == NULL) b->extreme = n;
     else if(b->compare(n->value, b->extreme->value) < 0) b->extreme = n;
}

static void merge(Binomial *b, DArray *a) {
     // Loop through every node in the array.
     // [NOTE]: I think we go from right to left, i.e. use removeDArray.
     while(sizeDArray(a) != 0) {
          BinomialNode *n = removeDArray(a);
          n->parent = n;
          // Consolidate b and node n.
          consolidate(b, n);
     }

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

// =============================================================================

int sizeBinomial(Binomial *b) {
     return b->size;
}

// =============================================================================
BinomialNode *bubbleUp(Binomial *b, BinomialNode *n) {
     // If n is the root of a subheap, return n;
     if(n->parent == n) {
          return n;
     // b's comparator says the n's value isn't more extreme than it's parent's
     } else if(b->compare(n->value, n->parent->value) > 0) {
          return n;
     } else {
          // Call the updater with n's value and n's parent.
          b->update(n->value, n->parent);
          // Call the updater with n's parent's value and n
          b->update(n->parent->value, n);
          // Swap the values of n and n's parent
          void *temp = n->value;
          n->value = n->parent->value;
          n->parent->value = temp;
          return bubbleUp(b, n->parent);
     }
}

void decreaseKeyBinomial(Binomial *b, BinomialNode *n, void *value) {
     // Set n's value to the new value.
     n->value = value;
     // Bubble up the new value using b's comparator.
     bubbleUp(b, n);
     // Update b's extreme value pointer, if necessary.
     if(b->extreme == NULL) b->extreme = n;
     else if(b->compare(n->value, b->extreme->value) < 0) b->extreme = n;
}

void *extractBinomial(Binomial *b) {
     // Set y to b's extreme.
     BinomialNode *y = b->extreme;
     // Remove y from b's root list by placing a NULL pointer in y's spot.
     int index = 0;
     for(index = 0; index < sizeDArray(b->rootlist); index++) {
          if(y == getDArray(b->rootlist, index)) {
               setDArray(b->rootlist, index, NULL);
               break;
          }
     }
     // The children of y are an array.. so Merge them into b's root list
     // via Merge.
     merge(b, y->children);
     // Decrement b's size.
     b->size--;
     // Store y's value.
     void *val = y->value;
     // Free the extreme node.
     free(y);
     // To find the new extreme value, one seraches the root list from degree
     // 0 to degree log(size of b) / log(2), inclusive.
     index = 0;
     while(index <= (int)(log((double) b->size)/log(2))) {
          // [TODO]: finish this up here.
     }


     return val;
}

void deleteBinomial(Binomial *b, BinomialNode *n) {
     decreaseKeyBinomial(b, n, NULL);
     extractBinomial(b);
}

// EOF
