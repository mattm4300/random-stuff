/* ============================================================================
 * FILENAME: sll.c
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Implementation file stack class and methods.
 *
 * NOTES:
 *   The associated header file for this file is "stack.h".
 *
 * VERSION: 1.0
 * ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "sll.h"

/* ============================================================================
 * newStack
 * ----------------------------------------------------------------------------
 * Creates a new stack.
 *
 * d: The associated display function to be used on the data type
 *    stored inside of the list nodes.
 *
 * returns: A pointer to a dynamically allocated stack object.
 * ============================================================================
*/
stack *newStack(void (*d)(FILE *, void *)) {
     // Allocate memory for a new stack and check to ensure the
     // allocation was successful.
     stack *items = malloc(sizeof(stack));
     if(items == 0) {
          fprintf(stderr, "out of memory.");
          exit(-1);
     }
     // Initialize the underlying SLL object the stack
     // is built on.
     items->list = newSLL(d);

     return items;
}

/* ============================================================================
 * push
 * ----------------------------------------------------------------------------
 * Pushes a value onto the top of the stack.
 *
 * items: The stack to store the value on top of.
 * value : The value to store on top of the stack.
 *
 * returns: void.
 * ============================================================================
*/
void push(stack *items, void *value) {
     // Insert the data at the head of the underlying SLL.
     insertSLL(items->list, STACK_TOP, value);
}

/* ============================================================================
 * pop
 * ----------------------------------------------------------------------------
 * Pops of the "top" value from a stack.
 *
 * items: The stack to which pop off the top value.
 *
 * returns: A generic data pointer.
 * ============================================================================
*/
void *pop(stack *items) {
     return removeSLL(items->list, STACK_TOP);
}

/* ============================================================================
 * peekStack
 * ----------------------------------------------------------------------------
 * Returns the data on the top of the stack.
 *
 * items: The stack to which return the top value.
 *
 * returns: A generic data pointer.
 * ============================================================================
*/
void *peekStack(stack *items) {
     return getSLL(items->list, STACK_TOP);
}

/* ============================================================================
 * sizeStack
 * ----------------------------------------------------------------------------
 * Returns the size of a stack.
 *
 * items: The stack to which return the size of.
 *
 * returns: An integer (the stack size).
 * ============================================================================
*/
int sizeStack(stack *items) {
     return sizeSLL(items->list);
}

/* ============================================================================
 * displayStack
 * ----------------------------------------------------------------------------
 * Displays the contents of a stack in a [x1,x2,x3,...,xN] style.
 *
 * items: The stack to which display.
 *
 * returns: void.
 * ============================================================================
*/
void displayStack(FILE *fp, stack *items) {
     displaySLL(fp, items->list);
}

// EOF
