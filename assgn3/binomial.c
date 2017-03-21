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

static int degree(BinomialNode *n) {
     if(sizeDArray(n->children == 0)) return 0;

     int degree = -1;
     int index = 0;
     for(index = 0; index < sizeDArray(n->children); index++) {
          int temp = degree(n->children[index]);
          if(temp > degree) degree = temp;
     }
     return degree;
}

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
     fprintf(fp, "-%d", degree(x));
     if(x->parent != x) {
          fprintf(fp, "(");
          x->display(fp, x->parent->value);
          fprintf(fp, "-%d", degree(x->parent));
          fprintf(fp, ")");
     }
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

static BinomialNode *combine(Binomial *b, BinomialNode *x, BinomialNode *y) {
     // If x more extreme than y:
     if(b->compare(x, y) < 0) {
          int i = degree(y);
          setDArray(x->children, i, y);
          y->parent = x;
          return x;
     // Else y more extreme than x:
     } else {
          int i = degree(x);
          setDArray(y->children, i, x);
          x->parent = y;
          return y;
     }
}

static consolidate(Binomial *b, BinomialNode *n) {
     int degree = sizeDArray(n->children);
     while(getDArray(b->rootlist, degree) != NULL) {
          n = combine(b, n, b->rootlist[degree]);
          b->rootlist[degree] = NULL;
          ++degree;
     }
     setDArray(b->rootlist, degree, n);
}

BinomialNode *insertBinomial(Binomial *b, void *value) {
     BinomialNode *n = newBinomialNode(value, b->display);
     n->parent = parent;
     n->children = newDArray(displayBinomialNode);

}

int sizeBinomial(Binomial *b) { return b->size; }
