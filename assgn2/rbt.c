#include "rbt.h"

typedef struct rbtValue {
     void *val;
     int freq;
     // black 0 red 1
     int color;
     void (*display)(FILE *,void *);
     int (*compare)(void *,void *);
} rbtValue;

static int color(rbtValue *v) {
     return v->color;
}

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

static int rbtComparator(void *a, void *b) {
     rbtValue *x = a;
     rbtValue *y = b;
     return x->compare(x->val, y->val);
}

static rbtValue *newRBTValue(void (*d)(FILE *, void *), int (*c)(void *, void *)) {
     rbtValue *newVal = malloc(sizeof(rbtValue));
     newVal->display = d;
     newVal->compare = c;
     newVal->val = NULL;
     newVal->freq = 1;
     newVal->color = 1;
     return newVal;
}

rbt *newRBT(void (*display)(FILE *,void *), int (*compare)(void *,void *)) {
     rbt *newTree = malloc(sizeof(rbt));
     newTree->tree = newBST(displayRBTValue, rbtComparator);
     newTree->display = display;
     newTree->compare = compare;
     newTree->size = 0;
     newTree->words = 0;
     return newTree;
}

static bstNode *getUncle(bstNode *n) {
     if(n->parent->left == n) {
          return n->parent->parent->right;
     } else {
          return n->parent->parent->left;
     }
}

static int isLeftChild(bstNode *n) {
     return n->parent->left == n;
}

static int isRightChild(bstNode *n) {
     return n->parent->right == n;
}

static int isLinear(bstNode *p, bstNode *n) {
     if(isLeftChild(p)) {
          if(isLeftChild(n)) return 1;
          else return 0;
     } else {
          if(isRightChild(n)) return 1;
          else return 0;
     }
}

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
               if(isLeftChild(p)) {
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
               if(isRightChild(p)) {
                    gp->right = n;
               } else {
                    gp->left = n;
               }
               n->parent = gp;
          }
     }
}

static void insertionFixupRBT(bst *tree, bstNode *n) {
     bstNode *uncle = NULL, *p = NULL, *gp = NULL, *prevP = NULL, *prevN = NULL;
     while(1) {
          if(tree->root == n) break;
          if(color((rbtValue *) n->parent->value) == 0) break;
          uncle = getUncle(n);
          p = n->parent;
          gp = n->parent->parent;
          // Uncle exists and its color is red.
          if(uncle != NULL && color(((rbtValue *) uncle->value)) == 1) {
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

void insertRBT(rbt *tree, void *val) {
     // Allocate a new rbt value.
     rbtValue *newVal = newRBTValue(tree->display, tree->compare);
     newVal->val = val;
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
          rbtValue *temp = n->value;
          temp->freq += 1;
          // We didn't put a new node into the underlying bst, so just
          // increment the word count.
          tree->words += 1;
     }
}

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

int sizeRBT(rbt *tree) {
     return tree->size;
}

int wordsRBT(rbt *tree) {
     return tree->words;
}

void statisticsRBT(rbt *tree, FILE *fp) {
     fprintf(fp, "Words/Phrases: %d\n", tree->words);
     statisticsBST(tree->tree, fp);
}

void displayRBT(FILE *fp, rbt *tree) {
     displayBST(fp, tree->tree);
}
