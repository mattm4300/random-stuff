/* =======================================================================
 * FILENAME: real.c
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *  Contains implementations for "real" data structure.
 *
 * PUBLIC FUNCTIONS:
 *   real *newReal(double)
 *   double getReal(real *)
 *   double setReal(real *, double)
 *   void displayReal(FILE *, void *)
 *   int compareReal(void *, void *)
 *   void freeReal(real *)
 *
 * NOTES:
 *   The associated header file for this file is "real.h".
 *
 * VERSION 1.0
 * =======================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "real.h"

extern void Fatal(char *, ...);

/* ============================================================================
 * newReal
 * ----------------------------------------------------------------------------
 * Returns a newly allocated real * object.
 *
 * x: The real value to be contained by the real object.
 *
 * returns: A real * object.
 * ============================================================================
*/
real *newReal(double x) {
     real *p = malloc(sizeof(real));
     if(p == 0) { Fatal("out of memory\n"); }
     p->value = x;
     return p;
}

/* ============================================================================
 * getReal
 * ----------------------------------------------------------------------------
 * Returns the double values stored in a real * object.
 *
 * v: The real object of which to return the double value stored within.
 *
 * returns: A double value.
 * ============================================================================
*/
double getReal(real *v) {
     return v->value;
}

/* ============================================================================
 * setReal
 * ----------------------------------------------------------------------------
 * Changes the double value stored within a real object to a new double value,
 * and returns the old value.
 *
 * v: The real object.
 * x: The new double value to store in the real object, v.
 *
 * returns: A double value.
 * ============================================================================
*/
double setReal(real *v, double x) {
     double old = v->value;
     v->value = x;
     return old;
}

/* ============================================================================
 * displayReal
 * ----------------------------------------------------------------------------
 * Writes the double value stored within a real object to a file pointer.
 *
 * fp: The file pointer to which write the double value.
 * v: The real object.
 *
 * returns: void.
 * ============================================================================
*/
void displayReal(FILE *fp, void *v) {
     fprintf(fp, "%f", getReal((real *) v));
}

/* ============================================================================
 * compareReal
 * ----------------------------------------------------------------------------
 * Compares two real * objects and returns whether one is greater than, less
 * than, or equal to the other.
 *
 * a: The primary real * object.
 * b: The secondary realr * object (the one that will be compared to a).
 *
 * returns: An int value. 0 if a = b, 1 if a > b, and -1 if a < b.
 * ============================================================================
*/
int compareReal(void *v, void *w) {
     return ((real *) v)->value - ((real *) w)->value;
}

/* ============================================================================
 * freeReal
 * ----------------------------------------------------------------------------
 * Frees a real * object from memory.
 *
 * v: The real object to be freed.
 *
 * returns: void.
 * ============================================================================
*/
void freeReal(real * v) {
     free(v);
}
