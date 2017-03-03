#include "vbst.h"

typedef struct vbstValue {
     void *val;
     int freq;
     void (*display)(FILE *,void *);
     int (*compare)(void *,void *);
} vbstValue;

vbst *newVBST(void (*display)(FILE *,void *),int (*compare)(void *,void *)) {
     vbst *newTree = malloc(sizeof(vbst));
     newTree->tree = newBST(display, compare);
     
}
