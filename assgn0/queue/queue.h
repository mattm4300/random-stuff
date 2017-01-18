/* ============================================================================
 * FILENAME: queue.h
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Header file for queue structs and function definitions.
 *
 * NOTES:
 *   The associated implementation file for this file is "queue.c".
 *
 * VERSION: 1.0
 * ============================================================================
*/

#ifndef __QUEUE_H_
#define __QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

// NOTE: we will use the head of the underlying SLL object
// as the "front" (enqueue) of the queue, and use the tail
// as the "back" (dequeue).

// The queue structure.
typedef struct queue {
     sll *list;
} queue;

extern queue *newQueue(void (*d)(FILE *,void *));   //constructor
extern void enqueue(queue *items,void *value);      //stores a generic value
extern void *dequeue(queue *items);                 //returns a generic value
extern void *peekQueue(queue *items);               //returns a generic value
extern int sizeQueue(queue *items);
extern void displayQueue(FILE *fp,queue *items);

#endif
