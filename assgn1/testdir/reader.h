/* =======================================================================
 * FILENAME: reader.h
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Header file for integer *, real *, and string * reader functions.
 *
 * NOTES:
 *   The associated implementation file for this file is "reader.c".
 *   These reader functions use the scanner functions published for
 *   free use by Dr. Lusth, University of Alabama.
 *
 * VERSION: 1.0
 * =======================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "scanner.h"
#include "queue.h"

#ifndef _READER_H_
#define _READER_H_

// Reader function pointer.
typedef void (*Reader)(FILE *, queue *);

Reader read;

// Function definitions.
extern void readIntegers(FILE *, queue *);
extern void readReals(FILE *, queue *);
extern void readStrings(FILE *, queue *);

#endif
