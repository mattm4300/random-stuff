/* =======================================================================
 * FILENAME: reader.c
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Contains implementations for integer *, real *, and string *
 *   reader functions.
 *
 * PUBLIC FUNCTIONS:
 *   void readIntegers(FILE *, queue *)
 *   void readReals(FILE *, queue *)
 *   void readStrings(FILE *, queue *)
 *
 *
 * NOTES:
 *   The associated header file for this file is "reader.h".
 *   These functions use the scanner functions defined and published
 *   for free use by Dr. Lusth, University of Alabama.
 *
 * VERSION 1.0
 * =======================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "reader.h"


/* ============================================================================
 * readIntegers
 * ----------------------------------------------------------------------------
 * Reads in and adds integers to a queue indefinitely, until EOF is read.
 *
 * fp: The file pointer to read from.
 * q: The queue to which add values.
 *
 * returns: void
 * ============================================================================
*/
void readIntegers(FILE *fp, queue *q) {
     int x = readInt(fp);
     while(!feof(fp)) {
          enqueue(q, newInteger(x));
          x = readInt(fp);
     }
}

/* ============================================================================
 * readReals
 * ----------------------------------------------------------------------------
 * Reads in and adds reals to a queue indefinitely, until EOF is read.
 *
 * fp: The file pointer to read from.
 * q: The queue to which add values.
 *
 * returns: void
 * ============================================================================
*/
void readReals(FILE *fp, queue  *q) {
     double x = readReal(fp);
     while(!feof(fp)) {
          enqueue(q, newReal(x));
          x = readReal(fp);
     }
}

/* ============================================================================
 * readStrings
 * ----------------------------------------------------------------------------
 * Reads in and adds strings to a queue indefinitely, until EOF is read.
 *
 * fp: The file pointer to read from.
 * q: The queue to which add values.
 *
 * returns: void
 * ============================================================================
*/
void readStrings(FILE *fp, queue *q) {
     char *x = readString(fp);
     while(!feof(fp)) {
          enqueue(q, newString(x));
          x = readString(fp);
     }
}
