#include <stdio.h>
#include <stdlib.h>
#include "reader.h"

void readIntegers(FILE *fp, queue *q) {
     int x = readInt(fp);
     while(!feof(fp)) {
          enqueue(q, newInteger(x));
          x = readInt(fp);
     }
}

void readReals(FILE *fp, queue  *q) {
     double x = readReal(fp);
     while(!feof(fp)) {
          enqueue(q, newReal(x));
          x = readReal(fp);
     }
}

void readStrings(FILE *fp, queue *q) {
     char *x = readString(fp);
     while(!feof(fp)) {
          enqueue(q, newString(x));
          x = readString(fp);
     }
}
