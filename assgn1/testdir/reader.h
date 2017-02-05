#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "scanner.h"
#include "queue.h"

#ifndef _READER_H_
#define _READER_H_

typedef void (*Reader)(FILE *, queue *);

Reader read;

extern void readIntegers(FILE *, queue *);
extern void readReals(FILE *, queue *);
extern void readStrings(FILE *, queue *);

#endif
