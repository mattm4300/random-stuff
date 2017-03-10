#include "rbt.h"
#include <stdio.h>
#include <stdlib.h>

// Struct used to make a bst act as a rbt.
typedef struct rbtValue {
     void *val;
     int freq;
     // black 0 red 1
     int color;
     void (*display)(FILE *,void *);
     int (*compare)(void *,void *);
} rbtValue;

// Returns the color of an rbtValue.
static int color(bstNode *v) {
     if(v == NULL) return 0;
     return ((rbtValue *) v->value)->color;
}

// Displays an rbtValue with all of its attributes.
static void displayRBTValue(FILE *fp, void *val) {
     rbtValue *v = (rbtValue *) val;
     v->display(fp, v->val);
     if(v->freq > 1) {
          fprintf(fp, "-%d", v->freq);
     }
     // color print.
     if(v->color == 0) {
          fprintf(fp, "-B");
     } else {
          fprintf(fp, "-R");
     }
}

// An rbtValue comparator that "unboxes" the rbtValues stored in the bst
// nodes and calls the comparator function stored in the rbtValue structs.
static int rbtComparator(void *a, void *b) {
     rbtValue *x = a;
     rbtValue *y = b;
     return x->compare(x->val, y->val);
}

// Returns a newly created rbtValue.
static rbtValue *newRBTValue(void (*d)(FILE *, void *), int (*c)(void *, void *)) {
     rbtValue *newVal = malloc(sizeof(rbtValue));
     newVal->display = d;
     newVal->compare = c;
     newVal->val = NULL;
     newVal->freq = 1;
     newVal->color = 0;
     return newVal;
}

// Returns a newly created rbt.
rbt *newRBT(void (*display)(FILE *,void *), int (*compare)(void *,void *)) {
     rbt *newTree = malloc(sizeof(rbt));
     newTree->tree = newBST(displayRBTValue, rbtComparator);
     newTree->display = display;
     newTree->compare = compare;
     newTree->size = 0;
     newTree->words = 0;
     return newTree;
}

// Returns true if the given node is a left child, otherwise returns false.
static int isLeftChild(bstNode *n) {
     return n->parent->left == n;
}

// returns true if the given node is a right child, otherwise returns false.
static int isRightChild(bstNode *n) {
     return n->parent->right == n;
}

// Returns the uncle of a node.
static bstNode *getUncle(bstNode *n) {
     if(isLeftChild(n->parent)) {
          return n->parent->parent->right;
     } else {
          return n->parent->parent->left;
     }
}

// Returns true if a node and its parent are in a linear format (left left or
// right right).
static int isLinear(bstNode *p, bstNode *n) {
     if(isLeftChild(p)) {
          if(isLeftChild(n)) return 1;
          else return 0;
     } else {
          if(isRightChild(n)) return 1;
          else return 0;
     }
}

// Rotates a node. The function knows which way to rotate based on whether it's
// a left or right child.
static void rotateRBTValue(bst *tree, bstNode *n) {
     bstNode *p = n->parent, *gp = n->parent->parent;
     bstNode *left = n->left, *right = n->right;
     // If n is a right child, rotate it left.
     if(isRightChild(n)) {
          n->left = p;
          p->parent = n;
          p->right = left;
          if(left != NULL) {
               left->parent = p;
          }
          if(p == tree->root) {
               n->parent = n;
               tree->root = n;
          } else {
               if(gp->left == p) {
                    gp->left = n;
               } else {
                    gp->right = n;
               }
               n->parent = gp;
          }
     // If n is a left child, rotate it right.
     } else {
          n->right = p;
          p->parent = n;
          p->left = right;
          if(right != NULL) {
               right->parent = p;
          }
          if(p == tree->root) {
               n->parent = n;
               tree->root = n;
          } else {
               if(gp->right == p) {
                    gp->right = n;
               } else {
                    gp->left = n;
               }
               n->parent = gp;
          }
     }
}


// Makes sure an rbt still has rbt form after a node insertion.
static void insertionFixupRBT(bst *tree, bstNode *n) {
     bstNode *uncle = NULL, *p = NULL, *gp = NULL, *prevP = NULL, *prevN = NULL;
     //int temploop = 1;
     while(1) {
          //printf("Foever loop: <%d>\n", temploop++);
          if(tree->root == n) break;
          p = n->parent;
          if(color(p) == 0) break;
          uncle = getUncle(n);
          gp = n->parent->parent;
          // Uncle exists and its color is red.
          if(color(uncle) == 1) {
               ((rbtValue *) p->value)->color = 0;
               ((rbtValue *) uncle->value)->color = 0;
               ((rbtValue *) gp->value)->color = 1;
               n = gp;
          // Uncle does not exist or is black.
          } else {
               if(isLinear(n->parent, n) == 0) {
                    prevP = p;
                    prevN = n;
                    rotateRBTValue(tree, n);
                    n = prevP;
                    p = prevN;
               }
               ((rbtValue *) p->value)->color = 0;
               ((rbtValue *) gp->value)->color = 1;
               rotateRBTValue(tree, p);
               break;
          }
     }
     ((rbtValue *) tree->root->value)->color = 0;
}

// Insert a value into an rbt.
void insertRBT(rbt *tree, void *val) {
     // Allocate a new rbt value.
     rbtValue *newVal = newRBTValue(tree->display, tree->compare);
     newVal->val = val;
     newVal->color = 1; // *****
     // See if the value is already in the tree.
     bstNode *n = findBSTNode(tree->tree, newVal);
     // if n is null, then the value is not in the tree so we need to
     // create a new rbtValue and store it in the tree.
     if(n == NULL) {
          // put the new rbt value into the underlying bst and collect the newly
          // inserted node.
          n = insertBST(tree->tree, newVal);
          // We need to call the fixup routine.
          insertionFixupRBT(tree->tree, n);
          // We put a new node into the rbt, so we need to increment BOTH
          // the rbt size and word count.
          tree->size += 1;
          tree->words += 1;
     // if n is not null, then we just need to increment the frequency of
     // the value.
     } else {
          // Increment the freqency inside the underlying node.
          rbtValue *temp = (rbtValue *) n->value;
          temp->freq += 1;
          // We didn't put a new node into the underlying bst, so just
          // increment the word count.
          tree->words += 1;
     }
}

// Returns the frequency of a value in a rbt tree.
int findRBT(rbt *tree, void *val) {
     rbtValue *temp = newRBTValue(tree->display, tree->compare);
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

// Returns the size of a rbt (# of nodes).
int sizeRBT(rbt *tree) {
     return tree->size;
}

// Returns the number of words in a tree, which is the sum of every frequency
// in all the nodes times the number of nodes.
int wordsRBT(rbt *tree) {
     return tree->words;
}

// Displays the statistics for the rbt.
void statisticsRBT(rbt *tree, FILE *fp) {
     fprintf(fp, "Words/Phrases: %d\n", tree->words);
     statisticsBST(tree->tree, fp);
}

// Displays the rbt itself.
void displayRBT(FILE *fp, rbt *tree) {
     displayBST(fp, tree->tree);
}
