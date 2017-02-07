#include <stdio.h>
#include <stdlib.h>
#include "comparator.h"

int intComparator(void *a, void *b) {
     int v1, v2;
     v1 = ((integer *) a)->value;
     v2 = ((integer *) b)->value;
     if(v1 == v2) {
          return 0;
     } else if(v1 < v2) {
          return -1;
     } else {
          return 1;
     }
}

int realComparator(void *a, void *b) {
     double v1, v2;
     v1 = ((real *) a)->value;
     v2 = ((real *) b)->value;
     if(v1 == v2) {
          return 0;
     } else if(v1 < v2) {
          return -1;
     } else {
          return 1;
     }
}

int stringComparator(void *a, void *b) {
     char *v1; char *v2;
     v1 = ((string *) a)->value;
     v2 = ((string *) b)->value;
     int val = strcmp(v1, v2);
     if(val > 0) {
          return 1;
     } else if(val < 0) {
          return -1;
     } else {
          return 0;
     }
}
