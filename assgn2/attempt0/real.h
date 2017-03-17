/* =======================================================================
 * FILENAME: real.h
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Header file "real" data structure.
 *
 * NOTES:
 *   The associated implementation file for this file is "real.c".
 *
 * VERSION: 1.0
 * =======================================================================
 */
#include <stdio.h>

#ifndef _REAL_H_
#define _REAL_H_

// The "real" data structure definition
typedef struct real {
     double value;
} real;

// Functio definitions
extern real *newReal(double);
extern double getReal(real *);
extern double setReal(real *, double);
extern void displayReal(FILE *, void *);
extern int compareReal(void *, void *);
extern void freeReal(real *);

#endif
