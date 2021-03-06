/*
 Author: Matthew Morgan

 Binomial heap implementation.


*/


#include <stdio.h>
#include <stdlib.h>
#include "binomial.h"
#include "queue.h"

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

// Returns the degree of a node.
static int degreeBinomialNode(BinomialNode *n) {
     return sizeDArray(n->children);
}

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
     if(n == NULL) {
          fprintf(stderr, "Something wrong. NULL passed to displayNode.");
          exit(-1);
     }
     n->display(fp, n->value);
     fprintf(fp, "-%d", degreeBinomialNode(n));
     if(n->parent != n) {
          fprintf(fp, "(");
          n->parent->display(fp, n->parent->value);
          fprintf(fp, "-%d)", degreeBinomialNode(n->parent));
     }
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
     b->rootlist = newDArray(d);
     b->extreme = NULL;
     b->size = 0;
     return b;
}

static BinomialNode *getSubHeap(DArray *a, int degree) {
     if(degree > sizeDArray(a)) {
          fprintf(stderr, "Error in getSubHeap!\n");
          exit(-1);
     } else if(degree == sizeDArray(a)) {
          return NULL;
     } else {
          return getDArray(a, degree);
     }
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

static void checkExtreme(Binomial *b, BinomialNode *n) {
     if(b->extreme == NULL) b->extreme = n;
     else if(b->compare(n->value, b->extreme->value) < 0) {
          b->extreme = n;
     }
}

static void setNewExtreme(Binomial *b) {
     b->extreme = NULL;
     int index = 0;
     for(index = 0; index < sizeDArray(b->rootlist); index++) {
          BinomialNode *n = getSubHeap(b->rootlist, index);
          if(n != NULL) {
               checkExtreme(b, n);
          }
     }
}

static void consolidate(Binomial *b, BinomialNode *n) {
     // Set degree to the number of n's children.
     int degree = degreeBinomialNode(n);
     // While b's rootlist at index degree is not empty.. loop.
     while(getSubHeap(b->rootlist, degree) != NULL) {
          // Set n to the combination of n and the subtree stored at the index.
          n = combine(b, n, getSubHeap(b->rootlist, degree));
          // Set b's slot at index degree to NULL.
          setDArray(b->rootlist, degree, NULL);
          // Increment the degree.
          ++degree;
          // [NOTE]: I'm pretty sure this if statement is mandatory.
          if(degree == sizeDArray(b->rootlist)) insertDArray(b->rootlist, NULL);
     }
     // Degree now indexes an empty slot, so place n at index degree, growing
     // the root list if necessary (handled by DArray class).
     setDArray(b->rootlist, degree, n);

}

static void merge(Binomial *b, DArray *a) {
     // Loop through every node in the array.
     // [NOTE]: I think we go from right to left, i.e. use removeDArray.
     int size =  sizeDArray(a);
     int index = 0;
     for(index = 0; index < size; index++){
          BinomialNode *n = (BinomialNode *) getDArray(a, index);
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

     checkExtreme(b, n);

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
     BinomialNode *np = bubbleUp(b, n);
     // Update b's extreme value pointer, if necessary.
     checkExtreme(b, np);
}



void *extractBinomial(Binomial *b) {
     // Set y to b's extreme.
     BinomialNode *y = b->extreme;
     // Remove y from b's root list by placing a NULL pointer in y's spot.
     setDArray(b->rootlist, degreeBinomialNode(y), NULL);
     // The children of y are an array.. so Merge them into b's root list
     // via Merge.
     merge(b, y->children);
     // Decrement b's size.
     b->size--;
     // Store y's value.
     void *val = y->value;
     // Free the extreme node.
     free(y);
     // Find the new extreme value.
     setNewExtreme(b);
     // Return the value that was in y.
     return val;
}

void deleteBinomial(Binomial *b, BinomialNode *n) {
     decreaseKeyBinomial(b, n, NULL);
     (void) extractBinomial(b);
}

static void printLevelOrder(FILE *fp, BinomialNode *n) {
     queue *q = newQueue(n->display);
     enqueue(q, n);
     enqueue(q, NULL);
     int level = 0;
     fprintf(fp, "%d: ", level);
     while(sizeQueue(q) != 0) {
          BinomialNode *temp = dequeue(q);
          if(temp == NULL) {
               fprintf(fp, "\n");
               if(sizeQueue(q) != 0) {
                    ++level;
                    enqueue(q, NULL);
                    fprintf(fp, "%d: ", level);
               }
          } else {
               displayBinomialNode(fp, temp);
               if(peekQueue(q) != NULL) fprintf(fp, " ");
               int index = 0;
               for(index = 0; index < sizeDArray(temp->children); index++) {
                    enqueue(q, (BinomialNode *) getSubHeap(temp->children, index));
               }
          }
     }
}

void displayBinomial(FILE *fp, Binomial *b) {
     if(sizeBinomial(b) == 0) {
          fprintf(fp, "0:\n");
          return;
     }

     int index = 0;
     for(index = 0; index < sizeDArray(b->rootlist); index++) {
          if(getSubHeap(b->rootlist, index) != NULL) {
               printLevelOrder(fp, (BinomialNode *) getSubHeap(b->rootlist, index));
               fprintf(fp, "----\n");
          }
     }
}


// EOF
