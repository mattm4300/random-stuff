#include "integer.h"
#include "real.h"
#include "string.h"

#ifndef _COMPARATOR_H_
#define _COMPARATOR_H_

typedef int (*Comparator)(void*,void*);
typedef void (*Printer)(FILE*,void*);

Comparator comp;
Printer print;

int intComparator(void *, void *);
int realComparator(void *, void *);
int stringComparator(void *, void *);

#endif
