/* ============================================================================
 * FILENAME: sll.h
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Header file for singly-linked list structs and function definitions.
 *
 * NOTES:
 *   The associated implementation file for this file is "sll.c".
 *
 * VERSION: 1.0
 * ============================================================================
*/


#ifndef __SLL_H_
#define __SLL_H_

#include <stdio.h>
#include <stdlib.h>


// The sllnode class.
typedef struct sllnode {
    void *value;
    struct sllnode *next;
} sllnode;

// The sll class.
typedef struct sll {
    sllnode *head;
    sllnode *tail;
    int size;
    void (*display)(FILE *, void *);
} sll;

// Function definitions.
extern sll *newSLL(void (*d)(FILE *, void *));
extern void insertSLL(sll *items, int index, void *value);
extern void *removeSLL(sll *items, int index);
extern void unionSLL(sll *recipient, sll *donor);
extern void *getSLL(sll *items, int index);
extern int sizeSLL(sll *items);
extern void displaySLL(FILE *, sll *items);

#endif
