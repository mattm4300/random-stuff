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

static int degree(BinomialNode *n) {
     if(sizeDArray(n->children) == 0) return 0;

     int dg = -1;
     int index = 0;
     for(index = 0; index < sizeDArray(n->children); index++) {
          int temp = degree((BinomialNode *) getDArray(n->children, index));
          if(temp > dg) dg = temp;
     }
     return dg;
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
     //
     printf("START_FUNC: displayBinomialNode\n");
     printf("Casting node...\n");
     //
     BinomialNode *x = (BinomialNode *) n; // "Unbox" the value.
     //
     printf("Done casting.\n");
     printf("NODE VALUE: "); x->display(stdout, x->value); printf("\n");
     printf("Starting display:\n");
     //
     x->display(fp, x->value);
     fprintf(fp, "-%d", degree(x));
     if(x->parent != x) {
          fprintf(fp, "(");
          x->display(fp, x->parent->value);
          fprintf(fp, "-%d", degree(x->parent));
          fprintf(fp, ")");
     }
     //
     printf("\nDisplay done.\n");
     printf("END_FUNC: displayBinomialNode\n");
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
     //
     printf("START_FUNC: combine\n");
     printf("Starting combine...\n");
     //

     // If x more extreme than y:
     if(b->compare(x, y) < 0) {
          int i = degree(y);
          //
          printf("Degree of y: %d\n", i);
          printf("Setting array...\n");
          //
          setDArray(x->children, i, y);
          //
          printf("Array set done.\n");
          //
          y->parent = x;
          //
          printf("Combine done.\n");
          printf("END_FUNC: combine\n");
          //
          return x;
     // Else y more extreme than x:
     } else {
          int i = degree(x);
          //
          printf("Degree of x: %d\n", i);
          printf("Setting array...\n");
          //
          setDArray(y->children, i, x);
          //
          printf("Array set done.\n");
          //
          x->parent = y;
          //
          printf("Combine done.\n");
          printf("END_FUNC: combine\n");
          //
          return y;
     }
}

static void consolidate(Binomial *b, BinomialNode *n) {
     //
     printf("START_FUNC: consolidate\n");
     printf("Starting combine loop...\n");
     //
     int dg = sizeDArray(n->children);
     while(getDArray(b->rootlist, dg) != NULL) {
          //
          printf("Loop beginning hit.\n");
          printf("Doing a combine...\n");
          //
          n = combine(b, n, getDArray(b->rootlist, dg));
          //
          printf("Combine finished.\n");
          printf("Setting array value at index (degree): %d\n", dg);
          //
          setDArray(b->rootlist, dg,  NULL);
          //
          printf("Array set done.\n");
          //
          ++dg;
     }
     //
     printf("Combine loop done.\n");
     printf("Doing final set...\n");
     printf("Inserting @ dg: %d\n", dg);
     //
     setDArray(b->rootlist, dg, n);
     //
     printf("final set done.\n");
     printf("END_FUNC: consolidate\n");
     //
}

BinomialNode *insertBinomial(Binomial *b, void *value) {
     //
     printf("START_FUNC: insertBinomial\n");
     printf("Attempting to insert: ");
     b->display(stdout, value); printf("\n");
     //
     printf("Creating node...\n");
     //
     BinomialNode *n = newBinomialNode(b->display, value);
     //
     printf("Done creating node.\n");
     printf("Consolidating...\n");
     //
     consolidate(b, n);
     //
     printf("Done Consolidating.\n");
     printf("Printing rootlist:\n");
     int temp = 0;
     for(temp = 0; temp < sizeDArray(b->rootlist); temp++) {
          printf("\t%d: ", temp);
          displayBinomialNode(stdout, getDArray(b->rootlist, temp));
     }
     printf("Done printing rootlist.\n");
     printf("END_FUNC: insertBinomial\n");
     //
     ++b->size;
     return n;
}

int sizeBinomial(Binomial *b) { return b->size; }

// Helper for displayBinomial
static void displaySubtree(FILE *fp, BinomialNode *n) {
     DArray *arr = newDArray(displayBinomialNode);
}

void displayBinomial(FILE *fp, Binomial *b) {
     int rootindex = 0;
     for(rootindex = 0; rootindex < sizeDArray(b->rootlist); ++rootindex) {
          displaySubtree(fp, getDArray(b->rootlist, rootindex));
          fprintf(fp, "----\n");
     }
}


// EOF
