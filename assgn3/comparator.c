/* =======================================================================
 * FILENAME: comparator.c
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Contains implementations for integer *, real *, and string *
 *   comparator functions.
 *
 * PUBLIC FUNCTIONS:
 *   int intComparator(void *, void *)
 *   int realComparator(void *, void *)
 *   int stringComparator(void *, void *)
 *
 * NOTES:
 *   The associated header file for this file is "comparator.h".
 *
 * VERSION 1.0
 * =======================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "comparator.h"

/* ============================================================================
 * intComparator
 * ----------------------------------------------------------------------------
 * Compares two integer * objects and returns whether one is greater than, less
 * than, or equal to the other.
 *
 * a: The primary integer * object.
 * b: The secondary integer * object (the one that will be compared to a).
 *
 * returns: An int value. 0 if a = b, 1 if a > b, and -1 if a < b.
 * ============================================================================
*/
int intComparator(void *a, void *b) {
     // Updated for assign3:
     if(a == NULL && b == NULL) return 0;
     else if(a == NULL) return -1;
     else if(b == NULL) return 1;

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

/* ============================================================================
 * realComparator
 * ----------------------------------------------------------------------------
 * Compares two real * objects and returns whether one is greater than, less
 * than, or equal to the other.
 *
 * a: The primary real * object.
 * b: The secondary real * object (the one that will be compared to a).
 *
 * returns: An int value. 0 if a = b, 1 if a > b, and -1 if a < b.
 * ============================================================================
*/
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

/* ============================================================================
 * stringComparator
 * ----------------------------------------------------------------------------
 * Compares two string * objects and returns whether one is greater than, less
 * than, or equal to the other.
 *
 * a: The primary string * object.
 * b: The secondary string * object (the one that will be compared to a).
 *
 * returns: An int value. 0 if a = b, 1 if a > b, and -1 if a < b.
 *
 * NOTES: The comparator is based on the strcmp function.
 * ============================================================================
*/
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
