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
