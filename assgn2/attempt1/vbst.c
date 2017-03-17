#include "vbst.h"
#include <stdio.h>
#include <stdlib.h>

// Struct used to make a bst act like a vbst.
typedef struct vbstValue {
     void *val;
     int freq;
     void (*display)(FILE *,void *);
     int (*compare)(void *,void *);
} vbstValue;

// Displays a vbstValue with all of its attributes.
static void displayVBSTValue(FILE *fp, void *val) {
     vbstValue *v = (vbstValue *) val;
     v->display(fp, v->val);
     if(v->freq > 1) {
          fprintf(fp, "-%d", v->freq);
     }
}

// A vbst comparator that "unboxes" the vbstValue stored in the bstNode
// nodes and calls the comparator function stored in the vbstValue structs.
static int vbstComparator(void *a, void *b) {
     vbstValue *x = a;
     vbstValue *y = b;
     return x->compare(x->val, y->val);
}

// Returns a newly created vbstValue.
static vbstValue *newVBSTValue(void (*d)(FILE *, void *), int (*c)(void *, void *)) {
     vbstValue *newVal = malloc(sizeof(vbstValue));
     newVal->display = d;
     newVal->compare = c;
     newVal->val = NULL;
     newVal->freq = 1;
     return newVal;
}

// Returns a newly created vbst.
vbst *newVBST(void (*display)(FILE *,void *), int (*compare)(void *,void *)) {
     vbst *newTree = malloc(sizeof(vbst));
     newTree->tree = newBST(displayVBSTValue, vbstComparator);
     newTree->display = display;
     newTree->compare = compare;
     newTree->size = 0;
     newTree->words = 0;
     return newTree;
}

// Inserts the given value into the vbst. If the value is already in the tree,
// the frequency of that value is simlpy incremented.
void insertVBST(vbst *tree, void *val) {
     // Allocate a new vbst value.
     vbstValue *newVal = newVBSTValue(tree->display, tree->compare);
     newVal->val = val;
     // See if the value is already in the tree.
     bstNode *n = findBSTNode(tree->tree, newVal);
     // if n is null, then the value is not in the tree so we need to
     // create a new vbstValue and store it in the tree.
     if(n == NULL) {
          // put the new vbst value into the underlying bst.
          insertBST(tree->tree, newVal);
          // We put a new node into the vbst, so we need to increment BOTH
          // the vbst size and word count.
          tree->size += 1;
          tree->words += 1;
     // if n is not null, then we just need to increment the frequency of
     // the value.
     } else {
          // Increment the freqency inside the underlying node.
          vbstValue *temp = n->value;
          temp->freq += 1;
          // We didn't put a new node into the underlying bst, so just
          // increment the word count.
          tree->words += 1;
     }
}

// Returns the freqency of a value in a vbst.  Returns null if the value
// is not in the tree.
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

// If the given value is in the tree, decrements the freqency of that value,
// otherwise the node is removed.
void deleteVBST(vbst *tree, void *val) {
     // Get the bst node containing the vbstValue.
     vbstValue *temp = newVBSTValue(tree->display, tree->compare);
     temp->val = val;
     bstNode *n = findBSTNode(tree->tree, temp);
     // Make sure the value was actually in the tree.
     if(n == NULL) {
          fprintf(stderr, "Value ");
          temp->display(stderr, temp->val);
          fprintf(stderr," not found.\n");
          return;
     }
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


// Returns the size of the vbst.
int sizeVBST(vbst *tree) {
     return tree->size;
}

// Returns the number of words in a tree, which is the sum of every frequency
// in all the nodes times the number of nodes.
int wordsVBST(vbst *tree) {
     return tree->words;
}

// Display the statistics for the vbst.
void statisticsVBST(vbst *tree, FILE *fp) {
     fprintf(fp, "Words/Phrases: %d\n", tree->words);
     statisticsBST(tree->tree, fp);
}

// Displays the vbst itself.
void displayVBST(FILE *fp, vbst *tree) {
     displayBST(fp, tree->tree);
}
