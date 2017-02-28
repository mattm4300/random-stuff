#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "queue.h"

bst *newBST(void (*display)(FILE *, void *), int (*compare)(void *, void *)) {
     bst *newTree = malloc(sizeof(bst));
     newTree->root = NULL;
     newTree->display = display;
     newTree->compare = compare;
     return newTree;
}

bstNode *insertBST(bst *tree, void *val) {
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
          tree->root = z;
     } else if(tree->compare(z->value, y->value) < 0) {
          y->left = z;
     } else {
          y->right = z;
     }
     return z;
}

int findBST(bst *tree, void *val) {
     // Empty tree.
     if(tree->root == NULL) {
          return 0;
     // Root value is value.
     } else if(tree->compare(tree->root->value, val) == 0) {
          return 1;
     // Search for value farther down in the tree.
     } else {
          // Progress down tree until value is found or null pointer
          // is reached.
          bstNode *spot = tree->root;
          while(1) {
               if(tree->compare(val, spot->value) < 0) {
                    spot = spot->left;
               } else {
                    spot = spot->right;
               }
               if(spot == NULL) {
                    return 0;
               } else if(tree->compare(spot->value, val) == 0) {
                    return 1;
               } else {
                    continue;
               }
          }
     }
}

bstNode *findBSTNode(bst *tree, void *val) {
     // Empty tree.
     if(tree->root == NULL) {
          return 0;
     // Root value is value.
     } else if(tree->compare(tree->root->value, val) == 0) {
          return tree->root;
     // Search for value farther down in the tree.
     } else {
          // Progress down tree until value is found or null pointer
          // is reached.
          bstNode *spot = tree->root;
          while(1) {
               if(tree->compare(val, spot->value) < 0) {
                    spot = spot->left;
               } else {
                    spot = spot->right;
               }
               if(spot == NULL) {
                    return 0;
               } else if(tree->compare(spot->value, val) == 0) {
                    return spot;
               } else {
                    continue;
               }
          }
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
     return n;
}

void pruneBSTNode(bstNode *n) {
     if(n->parent == NULL && n->left == NULL && n->right == NULL) {
          free(n);
          n = NULL;
     } else if(n->left == NULL && n->right == NULL) {
          if(n->parent->left == n) {
               free(n);
               n = NULL;
          } else {
               free(n);
               n = NULL;
          }
     } else {

     }
}

void displayBST(FILE *fp, bst *tree) {
     if(tree->root == NULL) { return; }
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
               tree->display(fp, x->value);
               if(x->parent != NULL) {
                    fprintf(fp, " (");
                    tree->display(fp, x->parent->value);
                    fprintf(fp, ") ");
               } else {
                    fprintf(fp, " (root)");
               }

               if(x->left != NULL) { enqueue(helpQueue, x->left); }
               if(x->right != NULL) { enqueue(helpQueue, x->right); }
          }
     }
     return;
}
