/* ============================================================================
 * FILENAME: stack.h
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Header file for stack structs and function definitions.
 *
 * NOTES:
 *   The associated implementation file for this file is "stack.c".
 *
 * VERSION: 1.0
 * ============================================================================
*/

#ifndef __STACK_H_
#define __STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

// The stack structure.
typedef struct stack {
     sll *list;
} stack;

// Special note: the stack will use the underlying SLL's head as the
// "top" of the stack.
#define STACK_TOP 0

extern stack *newStack(void (*d)(FILE *,void *));   //constructor
extern void push(stack *items, void *value);        //stores a generic value
extern void *pop(stack *items);                     //returns a generic value
extern void *peekStack(stack *items);               //returns a generic value
extern int sizeStack(stack *items);
extern void displayStack(FILE *,stack *items);

#endif
