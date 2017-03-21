/* =======================================================================
 * FILENAME: comparator.h
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Header file for integer *, real *, and string * comparator functions.
 *
 * NOTES:
 *   The associated implementation file for this file is "comparator.c".
 *
 * VERSION: 1.0
 * =======================================================================
 */


#include "integer.h"
#include "real.h"
#include "string.h"
#include <stdlib.h>
#include <string.h>

#ifndef _COMPARATOR_H_
#define _COMPARATOR_H_

// Comparator and Printer function pointers.
typedef int (*Comparator)(void*,void*);
typedef void (*Printer)(FILE*,void*);

Comparator comp;
Printer print;

// Function definitions.
int intComparator(void *, void *);
int realComparator(void *, void *);
int stringComparator(void *, void *);

#endif
