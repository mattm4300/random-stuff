#include "vbst.h"

typedef struct vbstValue {
     void *val;
     int freq;
     void (*display)(FILE *,void *);
     int (*compare)(void *,void *);
} vbstValue;

static void displayVBSTValue(FILE *fp, void *val) {
     vbstValue *v = (vbstValue *) val;
     v->display(fp, v->val);
     if(v->freq > 1) {
          fprintf(fp, "-%d", v->freq);
     }
     printf("vbstval display done.\n");
}

static int vbstComparator(void *a, void *b) {
     vbstValue *x = a;
     vbstValue *y = b;
     return x->compare(x->val, y->val);
}

static vbstValue *newVBSTValue(void (*d)(FILE *, void *), int (*c)(void *, void *)) {
     vbstValue *newVal = malloc(sizeof(vbstValue));
     newVal->display = d;
     newVal->compare = c;
     newVal->val = NULL;
     newVal->freq = 1;
     return newVal;
}

vbst *newVBST(void (*display)(FILE *,void *), int (*compare)(void *,void *)) {
     vbst *newTree = malloc(sizeof(vbst));
     newTree->tree = newBST(displayVBSTValue, vbstComparator);
     newTree->display = display;
     newTree->compare = compare;
     newTree->size = 0;
     newTree->words = 0;
     return newTree;
}

void insertVBST(vbst *tree, void *val) {
     // Allocate a new vbst value.
     vbstValue *newVal = newVBSTValue(tree->display, tree->compare);
     newVal->val = val;
     printf("insert potential: "); displayVBSTValue(stdout, newVal); printf("\n");
     // See if the value is already in the tree.
     printf("Checking for present value...");
     bstNode *n = findBSTNode(tree->tree, newVal);
     printf("result received.\n");
     // if n is null, then the value is not in the tree so we need to
     // create a new vbstValue and store it in the tree.
     if(n == NULL) {
          printf("case A:\n");
          // put the new vbst value into the underlying bst.
          insertBST(tree->tree, newVal);
          // We put a new node into the vbst, so we need to increment BOTH
          // the vbst size and word count.
          tree->size += 1;
          tree->words += 1;
     // if n is not null, then we just need to increment the frequency of
     // the value.
     } else {
          printf("case B:\n");
          // Increment the freqency inside the underlying node.
          vbstValue *temp = n->value;
          temp->freq += 1;
          // We didn't put a new node into the underlying bst, so just
          // increment the word count.
          tree->words += 1;
          // free up the newVal and temp;
          free(temp);
          free(newVal);
     }
}

int findVBST(vbst *tree, void *val) {
     vbstValue *temp = newVBSTValue(tree->display, tree->compare);
     temp->val = val;
     bstNode *n = findBSTNode(tree->tree, temp);
     if(n == NULL) {
          free(temp);
          return 0;
     } else {
          free(temp);
          temp = n->value;
          return temp->freq;
     }
}

void deleteVBST(vbst *tree, void *val) {
     // Get the bst node containing the vbstValue.
     vbstValue *temp = newVBSTValue(tree->display, tree->compare);
     temp->val = val;
     bstNode *n = findBSTNode(tree->tree, temp);
     temp = n->value;
     // If the freqency of the vbstValue > 1, simply decrement the freqency
     // count of the word.
     if(temp->freq > 1) {
               temp->freq -= 1;
               tree->words -= 1;
     // If the freqency is 1, we need to remove the whole node from the
     // underlying bst.
     } else {
          n = swapToLeafBSTNode(n);
          pruneBSTNode(tree->tree, n);
          tree->size -= 1;
          tree->words -= 1;
     }
}

int sizeVBST(vbst *tree) {
     return tree->size;
}

int wordsVBST(vbst *tree) {
     return tree->words;
}

void statisticsVBST(vbst *tree, FILE *fp) {
     fprintf(fp, "Words/Phrases: %d\n", tree->words);
     statisticsBST(tree->tree, fp);
}

void displayVBST(FILE *fp, vbst *tree) {
     displayBST(fp, tree->tree);
}
