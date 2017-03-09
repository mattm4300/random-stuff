#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "queue.h"

bst *newBST(void (*display)(FILE *, void *), int (*compare)(void *, void *)) {
     bst *newTree = malloc(sizeof(bst));
     newTree->root = NULL;
     newTree->size = 0;
     newTree->display = display;
     newTree->compare = compare;
     return newTree;
}

bstNode *insertBST(bst *tree, void *val) {
     ++tree->size;
     bstNode *y = NULL;
     bstNode *x = tree->root;
     bstNode *z = malloc(sizeof(bstNode));
     z->value = val;
     z->parent = z->right = z->left = NULL;
     while(x != NULL) {
          y = x;
          if(tree->compare(z->value, x->value) < 0) {
               x = x->left;
          } else {
               x = x->right;
          }
     }
     z->parent = y;
     if(y == NULL) {
          z->parent = z;
          tree->root = z;
     } else if(tree->compare(z->value, y->value) < 0) {
          y->left = z;
     } else {
          y->right = z;
     }
     return z;
}

int findBST(bst *tree, void *val) {
     if(tree->root == NULL) return 0;
     else {
          bstNode *spot = tree->root;
          while(spot != NULL) {
               if(tree->compare(val, spot->value) == 0) {
                    return 1;
               } else if(tree->compare(val, spot->value) < 0) {
                    spot = spot->left;
               } else {
                    spot = spot->right;
               }
          }
          return 0;
     }
}

bstNode *findBSTNode(bst *tree, void *val) {
     if(tree->root == NULL) return NULL;
     else {
          bstNode *spot = tree->root;
          while(spot != NULL) {
               if(tree->compare(val, spot->value) == 0) {
                    return spot;
               } else if(tree->compare(val, spot->value) < 0) {
                    spot = spot->left;
               } else {
                    spot = spot->right;
               }
          }
          return spot;
     }
}

bstNode *swapToLeafBSTNode(bstNode *n) {
     bstNode *spot;
     void *val;
     if(n->left == NULL && n->right == NULL) {
          return n;
     } else if(n->left != NULL) {
          spot = n->left;
          while(spot->right != NULL) {
               spot = spot->right;
          }
          val = n->value;
          n->value = spot->value;
          spot->value = val;
     } else {
          spot = n->right;
          while(spot->left != NULL) {
               spot = spot->left;
          }
          val = n->value;
          n->value = spot->value;
          spot->value = val;
     }
     return swapToLeafBSTNode(spot);
}

void pruneBSTNode(bst *tree, bstNode *n) {
     --tree->size;
     if(n == tree->root && n->left == NULL && n->right == NULL) {
          free(n);
          n = NULL;
          tree->root = NULL;
     } else if(n->left == NULL && n->right == NULL) {
          if(n->parent->left == n) {
               n->parent->left = NULL;
               free(n);
          } else {
               n->parent->right = NULL;
               free(n);
          }
     } else {
          printf("error\n");
     }
}

int sizeBST(bst *tree) {
     return tree->size;
}

static int maxHeight(bstNode *n) {
     if(n == NULL) return 0;
     int leftHeight = maxHeight(n->left);
     int rightHeight = maxHeight(n->right);
     if(leftHeight > rightHeight) {
          return leftHeight + 1;
     } else {
          return rightHeight + 1;
     }
}

static int minHeight(bst *tree) {
     if(tree->root == NULL) return 0;
     queue *q = newQueue(tree->display);
     enqueue(q, tree->root);
     enqueue(q, NULL);
     int depth = 1;
     while(sizeQueue(q)) {
          bstNode *x = dequeue(q);
          if(x == NULL) {
               enqueue(q, NULL);
               ++depth;
          } else if(x->left == NULL || x->right == NULL) {
               return depth;
          } else {
               if(x->left != NULL) enqueue(q, x->left);
               if(x->right != NULL) enqueue(q, x->right);
          }
     }
     return depth;
}

void statisticsBST(bst *tree, FILE *fp) {
     fprintf(fp, "Nodes: %d\n", sizeBST(tree));
     fprintf(fp, "Minimum depth: %d\n", minHeight(tree));
     fprintf(fp, "Maximum depth: %d\n", maxHeight(tree->root));
}

static int isLeftChild(bstNode *n) {
     return n == n->parent->left;
}

static int isRightChild(bstNode *n) {
     return n == n->parent->right;
}

void displayBST(FILE *fp, bst *tree) {
     if(tree->root == NULL) {
          fprintf(fp, "0:\n");
          return;
     }
     queue *helpQueue = newQueue(tree->display);
     enqueue(helpQueue, tree->root);
     enqueue(helpQueue, NULL);
     int currentLevel = 0;
     fprintf(fp, "%d: ", currentLevel);
     while(sizeQueue(helpQueue)) {
          bstNode *x = dequeue(helpQueue);
          if(!sizeQueue(helpQueue)) {
               fprintf(fp, "\n");
               break;
          }
          else if(x == NULL) {
               fprintf(fp,"\n");
               enqueue(helpQueue, NULL);
               ++currentLevel;
               if(sizeQueue(helpQueue) != 1) {
                    fprintf(fp, "%d: ", currentLevel);
               }
          } else {
               if(x->left == NULL && x->right == NULL) fprintf(fp, "=");
               tree->display(fp, x->value);
               fprintf(fp, "(");
               tree->display(fp, x->parent->value);
               fprintf(fp, ")");
               if(isLeftChild(x)) fprintf(fp, "-l");
               else if (isRightChild(x)) fprintf(fp, "-r");
               else fprintf(fp, "-");
               if(peekQueue(helpQueue) != NULL) fprintf(fp, " ");
               if(x->left != NULL) { enqueue(helpQueue, x->left); }
               if(x->right != NULL) { enqueue(helpQueue, x->right); }
          }
     }
     return;
}
