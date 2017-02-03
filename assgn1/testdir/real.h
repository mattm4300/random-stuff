#include <stdio.h>

#ifndef _REAL_H_
#define _REAL_H_

typedef struct real {
     double value;
} real;

extern real *newReal(double);
extern double getReal(real *);
extern double setReal(real *, double);
extern void displayReal(FILE *, void *);
extern int compareReal(void *, void *);
extern void freeReal(real *);

#endif
