/* ============================================================================
 * FILENAME: queue.c
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Implementation file for queue class and methods.
 *
 * NOTES:
 *   The associated header file for this file is "queue.h".
 *   For naming conventions, consult queue.h.
 *
 * VERSION: 1.0
 * ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* ============================================================================
 * newQueue
 * ----------------------------------------------------------------------------
 * Creates a new queue.
 *
 * d: The associated display function to be used on the data type
 *    stored inside of the list nodes.
 *
 * returns: A pointer to a dynamically allocated queue object.
 * ============================================================================
*/
queue *newQueue(void (*d)(FILE *, void *)) {
     // Allocate memory for a new queue and check to ensure the
     // allocation was successful.
     queue *items = malloc(sizeof(queue));
     if(items == 0) {
          fprintf(stderr, "out of memory");
          exit(-1);
     }
     // Initialize the underlying SLL object the queue
     // is built on.
     items->list = newSLL(d);

     return items;
}

/* ============================================================================
 * enqueue
 * ----------------------------------------------------------------------------
 * Pushes a value onto the back of the queue.
 *
 * items: The queue to push the value to.
 * value : The value to store on the back of the queue.
 *
 * returns: void.
 * ============================================================================
*/
void enqueue(queue *items, void *value) {
     // Insert data at the head of the underlying SLL.
     insertSLL(items->list, items->list->size, value);
}

/* ============================================================================
 * dequeue
 * ----------------------------------------------------------------------------
 * Removes and returns the data at the front of the queue.
 *
 * items: The queue to which remove the front from.
 *
 * returns: A generic data pointer.
 * ============================================================================
*/
void *dequeue(queue *items) {
     return removeSLL(items->list, 0);
}

/* ============================================================================
 * peekQueue
 * ----------------------------------------------------------------------------
 * Returns the data at the front of the queue.
 *
 * items: The queue to which return the front from.
 *
 * returns: A generic data pointer.
 * ============================================================================
*/
void *peekQueue(queue *items) {
     return getSLL(items->list, 0);
}

/* ============================================================================
 * sizeQueue
 * ----------------------------------------------------------------------------
 * Returns the size of a queue.
 *
 * items: The queue to which return the size of.
 *
 * returns: An integer (the queue size).
 * ============================================================================
*/
int sizeQueue(queue *items) {
     return items->list->size;
}

/* ============================================================================
 * displayQueue
 * ----------------------------------------------------------------------------
 * Displays the contents of a queue in a [x1,x2,x3,...,xN] style.
 *
 * items: The queue to which display.
 *
 * returns: void.
 * ============================================================================
*/
void displayQueue(FILE *fp, queue *items) {
     displaySLL(fp, items->list);
}

// EOF
