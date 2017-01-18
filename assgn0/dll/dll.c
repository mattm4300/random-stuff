/* ============================================================================
 * FILENAME: dll.c
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Contains implementations for doubly-linked list class methods.
 *
 * PUBLIC FUNCTIONS:
 *   dll *newDLL(void (*d)(FILE *, void *))
 *   void insertDLL(dll *items, int index, void *value)
 *   void *removeDLL(dll *items, int index)
 *   void unionDLL(dll *recipient, dll *donor)
 *   void *getDLL(dll *items, int index)
 *   int sizeDLL(dll *items)
 *   void displayDLL(FILE *, dll *items)
 *
 * NOTES:
 *   The associated header file for this file is "dll.h".
 *
 * VERSION: 1.0
 * ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

/* ============================================================================
 * newDLL
 * ----------------------------------------------------------------------------
 * Creates a new doubly-linked list.
 *
 * d: The associated display function to be used on the data type
 *    stored inside of the list nodes.
 *
 * returns: A pointer to a dynamically allocated DLL object.
 * ============================================================================
*/
dll *newDLL(void (*d)(FILE *, void *)) {
     // Allocate memory for a new list and check to ensure that the
     // allocation was successful.
     dll *items = malloc(sizeof(dll));
     if(items == 0) {
          fprintf(stderr, "out of memory");
          exit(-1);
     }
     // Initialize the DLL's values.
     items->head = 0;
     items->tail = 0;
     items->size = 0;
     items->display = d;

     return items;
}

/* ============================================================================
 * insertDLL
 * ----------------------------------------------------------------------------
 * Insert a value into the list at the user's specified index.
 *
 * items: the list to which insert the data.
 * index: The index at which to insert the data.
 * value: The data to insert.
 *
 * returns: void.
 * ============================================================================
*/
void insertDLL(dll *items, int index, void *value) {
     // In the case that the list is empty (items->size == 0):
     if(items->size == 0) {
          // Allocate memory for the node to be inserted into the list,
          // and point the list's head and tail node pointers to the newly
          // constructed node.
          items->head = malloc(sizeof(dllnode));
          items->tail = items->head;
          // Since this is a DLL, we need to ensure that the previous and
          // next pointers wrap back around to the same node:
          items->head->next = items->head;
          items->head->previous = items->head;
          // Set the node's value.
          items->head->value = value;
          // Finally, increment the size of the dll.
          ++items->size;
     // In the case that the list is non-empty:
     } else if(items->size > 0) {
          // If the data is to be inserted at the head of the list:
          if(index == 0) {
               // Allocate memory for a new node and set its member's data.
               dllnode *newnode = malloc(sizeof(dllnode));
               newnode->value = value;
               // Set the new node's next pointer to the current head,
               // and set the head's previous pointer to the new node.
               newnode->next = items->head;
               items->head->previous = newnode;
               // Set the new node as the new head.
               items->head = newnode;
               // Set the new head's previous pointer to the tail, and the
               // tail's pointer to the new head.
               items->head->previous = items->tail;
               items->tail->next = items->head;
               // Incremtn the size.
               ++items->size;
          // If inserting data at the tail of the list:
          } else if(index == items->size) {
               // Allocate memory for a new node and set its member's data.
               dllnode *newnode = malloc(sizeof(dllnode));
               newnode->value = value;
               // Set the new node's next pointer to the current head,
               // and set the head's previous pointer to the new node.
               newnode->next = items->head;
               items->head->previous = newnode;
               // Set the current tail's next pointer to the new node,
               // and set the new node's previous pointer to the current tail.
               items->tail->next = newnode;
               newnode->previous = items->tail;
               // Set the new node as the new tail.
               items->tail = newnode;
               // Incremtn the size.
               ++items->size;
          // If data is to be inserted someplace in the middle of the list:
          } else {
               // Allocate memory for a new node and set its member's data.
               dllnode *newnode = malloc(sizeof(dllnode));
               newnode->value = value;
               // Create a tracking node pointer and counter.
               dllnode *spot = items->head;
               int counter = 0;
               // Loop to the node just before the insert index.
               while(counter < index - 1) {
                    spot = spot->next;
                    ++counter;
               }
               // Set the new node's previous pointer to the spot, and
               // set the new node's next pointer to the spot's next pointer.
               newnode->previous = spot;
               newnode->next = spot->next;
               // Set the spot's next pointer to the new node.
               spot->next = newnode;
               // Set the new node's next previous pointer to the new node.
               newnode->next->previous = newnode;
               // Increment the size.
               ++items->size;
          }
     }
}

// EOF
