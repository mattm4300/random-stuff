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
     if((items->size == 0) && (index == 0)) {
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
               // Increment the size.
               ++items->size;
          // If data is to be inserted someplace in the middle of the list:
          } else {
               // If index is closer to head than tail:
               if(index <= (items->size / 2)) {
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
               // If index is closer to the tail than head:
               } else {
                    // Allocate memory for a new node and set its member's data.
                    dllnode *newnode = malloc(sizeof(dllnode));
                    newnode->value = value;
                    // Create a tracking node pointer and counter.
                    dllnode *spot = items->tail;
                    int counter = 0;
                    // Loop to the node just before the insert index.
                    while(counter < (items->size - index)) {
                         spot = spot->previous;
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
}


/* ============================================================================
 * removeDLL
 * ----------------------------------------------------------------------------
 * Removes the data at a given index from a list and returns the data
 * back to the user.
 *
 * items: The list to which remove data.
 * index: The index at which to remove the data.
 *
 * returns: The data removed from the list.
 * ============================================================================
*/
void *removeDLL(dll *items, int index) {
     // If removing from the head of the list:
     if(index == 0) {
          // Go ahead and save the return value.
          void *value = items->head->value;
          // Create a temporary node pointer to point at the current head,
          // and move the head pointer to the pointer's next pointer.
          dllnode *temp = items->head;
          items->head = items->head->next;
          // Set the new head's previous point to the tail, and set the tail's
          // next pointer to the new head.
          items->head->previous = items->tail;
          items->tail->next = items->head;
          // Free the old head.
          free(temp);
          // Decrement the size and return the extracted value.
          --items->size;
          return value;
     // If removing form the back (tail) of the list:
     } else if(index == items->size - 1) {
          // Go ahead and save the return value.
          void *value = items->tail->value;
          // Create a temporary node pointer to point at the current tail,
          // and move the tail pointer to the pointer's previous pointer.
          dllnode *temp = items->tail;
          items->tail = items->tail->previous;
          // Set the new tail's next pointer to the head, and set the head's
          // previous pointer to the new tail.
          items->tail->next = items->head;
          items->head->previous = items->tail;
          // Free the old tail.
          free(temp);
          // Decrement the size and return the extracted value.
          --items->size;
          return value;
     // If removing from someplace in the middle of the list:
     } else {
          // If index is closer to head than tail:
          if(index <= (items->size / 2)) {
               // Create a placeholder node pointer and associated counter.
               dllnode *spot = items->head;
               int counter = 0;
               // Advance to the node before the current index node.
               while(counter < index - 1) {
                    spot = spot->next;
                    ++counter;
               }
               // Save the value.
               void *value = spot->next->value;
               // Create a temporary node pointer to keep a reference to the
               // next node.
               dllnode *temp = spot->next;
               // Set the placeholder node pointer's next pointer to the
               // next, next node.
               spot->next = spot->next->next;
               // Set the spot's next, next node's previous pointer back to spot.
               spot->next->previous = spot;
               // Free the old node.
               free(temp);
               // Decrement the size and return the value.
               --items->size;
               return value;
          // If the index is closer to tail than head:
          } else {
               // Create a placeholder node pointer and associated counter.
               dllnode *spot = items->tail;
               int counter = 0;
               // Advance to the node before the current index node.
               while(counter < (items->size - index)) {
                    spot = spot->previous;
                    ++counter;
               }
               // Save the value.
               void *value = spot->next->value;
               // Create a temporary node pointer to keep a reference to the
               // next node.
               dllnode *temp = spot->next;
               // Set the placeholder node pointer's next pointer to the
               // next, next node.
               spot->next = spot->next->next;
               // Set the spot's next, next node's previous pointer back to spot.
               spot->next->previous = spot;
               // Free the old node.
               free(temp);
               // Decrement the size and return the value.
               --items->size;
               return value;
          }
     }
}

/* ============================================================================
 * unionDLL
 * ----------------------------------------------------------------------------
 * Joins two DLLs together.
 *
 * recipient: The list to which keep a reference to (the first part of the
 * 	   	    joined lists).
 * donor: The list to which join to the tail of the recipient list (the second
 * 		part of the joined lists.)
 *
 * returns: void.
 * ============================================================================
*/
void unionDLL(dll *recipient, dll *donor) {
     // Make the recipient's tail->next pointer point to the
     // head of the donor list, and make the donors's head->previous
     // pointer point to the tail of the recipient list.
     recipient->tail->next = donor->head;
     donor->head->previous = recipient->tail;
     // Make the recipient's head->previous pointer point to the tail
     // of the donor list, and make the donor's tail->next pointer
     // point to the head of the recipient list.
     recipient->head->previous = donor->tail;
     donor->tail->next = recipient->head;
     // Change the recipient's tail to the donor's tail.
     recipient->tail = donor->tail;
     // Add the donor's size to the recipient's size.
     recipient->size += donor->size;
     // Make the donor list an empty list.
     donor->head = donor->tail = 0;
     donor->size = 0;
}

/* ============================================================================
 * getDLL
 * ----------------------------------------------------------------------------
 * Returns the data stored at a given index in the list.
 *
 * items: The list to which extract data from.
 * index: The index at which to extract data.
 *
 * returns: The data stored at the given 0-based index of the list.
 * ============================================================================
*/
void *getDLL(dll *items, int index) {
     // If getting from the head:
     if(index == 0) {
          return items->head->value;
     // If getting from the tail:
     } else if(index == sizeDLL(items) - 1) {
          return items->tail->value;
     // If getting from someplace in the middle:
     } else {
          // If index is closer to head than tail:
          if(index <= (items->size / 2)) {
               // Create a placeholder pointer and associated counter.
               dllnode *spot = items->head;
               int counter = 0;
               // Advance to the desired index.
               while(counter < index) {
                    spot = spot->next;
                    ++counter;
               }
               // Return the data stored at the desired index.
               return spot->value;
          // If index is closer to tail than head:
          } else {
               // Create a placeholder pointer and associated counter.
               dllnode *spot = items->tail;
               int counter = 0;
               // Advance to the desired index.
               while(counter < (items->size - index - 1)) {
                    spot = spot->previous;
                    ++counter;
               }
               // Return the data stored at the desired index.
               return spot->value;
          }
     }
}

/* ============================================================================
 * sizeDLL
 * ----------------------------------------------------------------------------
 * Returns the current size of a DLL.
 *
 * items: The list of which to determine the size.
 *
 * returns: The items->size member of the given list.
 * ============================================================================
*/
int sizeDLL(dll *items) {
     return items->size;
}

/* ============================================================================
 * displayDLL
 * ----------------------------------------------------------------------------
 * Displays the contents of a DLL in a [x1,x2,x3,...,x4] style.
 *
 * fp: The file (generally stdout) to which write the list.
 * items: The list to write out.
 *
 * returns: void.
 * ============================================================================
*/
void displayDLL(FILE *fp, dll *items) {
     // If the list is empty, print out an empty list.
     if(items->size == 0) {
          fprintf(fp, "[]");
     // If the list has 1 element, print just that element.
     } else if(items->size == 1) {
          fprintf(fp, "[");
          items->display(fp, items->head->value);
          fprintf(fp, "]");
     // If the list has >1 element, print out all the elements.
     } else {
          fprintf(fp, "[");
          dllnode *spot = items->head;
          int counter = 0;
          while(counter < items->size) {
               items->display(fp, spot->value);
               if(counter + 1 == items->size) {
                    break;
               } else {
                    printf(",");
                    spot = spot->next;
                    ++counter;
               }
          }
          printf("]");
     }
}


// EOF
