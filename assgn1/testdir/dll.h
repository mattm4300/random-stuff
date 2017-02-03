/* ============================================================================
 * FILENAME: dll.h
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Header file for doubly-linked list structs and function definitions.
 *
 * NOTES:
 *   The associated implementation file for this file is "dll.c".
 *
 * VERSION: 1.0
 * ============================================================================
*/

#ifndef _DLL_H_
#define _DLL_H_

#include <stdio.h>
#include <stdlib.h>

// The dllnode class.
typedef struct dllnode {
     void *value;
     struct dllnode *next;
     struct dllnode *previous;
} dllnode;

// The dll class.
typedef struct dll {
     dllnode *head;
     dllnode *tail;
     int size;
     void (* display)(FILE *, void *);
} dll;

// Function definitions.
extern dll *newDLL(void (*d)(FILE *, void *));
extern void insertDLL(dll *items, int index, void *value);
extern void *removeDLL(dll *items, int index);
extern void unionDLL(dll *recipient, dll *donor);
extern void *getDLL(dll *items, int index);
extern int sizeDLL(dll *items);
extern void displayDLL(FILE *, dll *items);

#endif
