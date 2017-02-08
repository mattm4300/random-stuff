/* =======================================================================
 * FILENAME: string.c
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *  Contains implementations for "string" data structure.
 *
 * PUBLIC FUNCTIONS:
 *   string *newString(double)
 *   double getString(string *)
 *   double setString(string *, double)
 *   void displayString(FILE *, void *)
 *   int compareString(void *, void *)
 *   void freeString(string *)
 *
 * NOTES:
 *   The associated header file for this file is "string.h".
 *
 * VERSION 1.0
 * =======================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "string.h"

extern void Fatal(char *, ...);

/* ============================================================================
 * newString
 * ----------------------------------------------------------------------------
 * Returns a newly allocated string * object.
 *
 * x: The string value to be contained by the string object.
 *
 * returns: A string * object.
 * ============================================================================
*/
string *newString(char *x) {
     string *p = malloc(sizeof(string));
     if(p == 0) { Fatal("out of memory\n"); }
     p->value = malloc(sizeof(strlen(x)));
     strcpy(p->value, x);
     return p;
}

/* ============================================================================
 * getString
 * ----------------------------------------------------------------------------
 * Returns the double values stored in a string * object.
 *
 * v: The string object of which to return the double value stored within.
 *
 * returns: A double value.
 * ============================================================================
*/
char *getString(string *v) {
     return v->value;
}

/* ============================================================================
 * setString
 * ----------------------------------------------------------------------------
 * Changes the double value stored within a string object to a new double value,
 * and returns the old value.
 *
 * v: The string object.
 * x: The new double value to store in the string object, v.
 *
 * returns: A double value.
 * ============================================================================
*/
char *setString(string *v, char *x) {
     char *old = malloc(sizeof(strlen(v->value)));
     strcpy(old, v->value);
     free(v->value);
     v->value = malloc(sizeof(strlen(x)));
     strcpy(v->value, x);
     return old;
}

/* ============================================================================
 * displayString
 * ----------------------------------------------------------------------------
 * Writes the double value stored within a string object to a file pointer.
 *
 * fp: The file pointer to which write the double value.
 * v: The string object.
 *
 * returns: void.
 * ============================================================================
*/
void displayString(FILE *fp, void *v) {
     fprintf(fp, "\"%s\"", getString((string *) v));
}

/* ============================================================================
 * compareString
 * ----------------------------------------------------------------------------
 * Compares two string * objects and returns whether one is greater than, less
 * than, or equal to the other.
 *
 * a: The primary string * object.
 * b: The secondary stringr * object (the one that will be compared to a).
 *
 * returns: An int value. 0 if a = b, 1 if a > b, and -1 if a < b.
 * ============================================================================
*/
int compareString(void *v, void *w) {
     return strcmp(((string *) v)->value, ((string *) w)->value);
}

/* ============================================================================
 * freeString
 * ----------------------------------------------------------------------------
 * Frees a string * object from memory.
 *
 * v: The string object to be freed.
 *
 * returns: void.
 * ============================================================================
*/
void freeString(string *v) {
     free(v);
}
