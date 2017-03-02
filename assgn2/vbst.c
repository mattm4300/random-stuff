#include "vbst.h"

typedef struct vbstValue {
     void *val;
     int freq;
     void (*display)(FILE *,void *);
     int (*compare)(void *,void *);
} vbstValue;
