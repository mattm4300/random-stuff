#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

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
          printf("X was not null.\n");
          y = x;
          printf("comparing\n");
          printf("X val: "); tree->display(stdout, x->value); printf("\n");
          if(tree->compare(z->value, x->value) < 0) {
               printf("z val was less than x val\n");
               x = x->left;
          } else {
               printf("z val was greater than x val\n");
               x = x->right;
          }
     }
     printf("spot1\n");
     z->parent = y;
     if(y == NULL) {
          tree->root = z;
     } else if(tree->compare(z->value, y->value) < 0) {
          y->left = z;
     } else {
          y->right = z;
     }
     printf("Spot3\n");
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
