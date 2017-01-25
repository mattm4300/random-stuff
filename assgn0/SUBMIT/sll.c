/* ============================================================================
 * FILENAME: sll.c
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Contains implementations for singly-linked list class methods.
 *
 * PUBLIC FUNCTIONS:
 *   sll * newSLL(void (*d)(FILE *, void *))
 *   void insertSLL(sll *items, int index, void *value)
 *   void *removeSLL(sll *items, int index)
 *   void unionSLL(sll *recipient, sll *donor)
 *   void *getSLL(sll *items, int index)
 *   int sizeSLL(sll *items)
 *   displaySLL(FILE *, sll *items)
 *
 * NOTES:
 *   The associated header file for this file is "sll.h".
 *
 * VERSION: 1.0
 * ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

/* ============================================================================
 * newSLL
 * ----------------------------------------------------------------------------
 * Creates a new singly-linked list.
 *
 * d: The associated display function to be used on the data type
 *    stored inside of the list nodes.
 *
 * returns: A pointer to a dynamically allocated SLL object.
 * ============================================================================
*/
sll *newSLL(void (*d)(FILE *, void *)) {
	// Allocate memory for a new list and check to ensure that the
	// allocation was successful.
	sll *items = malloc(sizeof(sll));
	if(items == 0) {
		fprintf(stderr, "out of memory.");
		exit(-1);
	}
	// Initialize the SLL's values.
	items->head = 0;
	items->tail = 0;
	items->size = 0;
	items->display = d;

	return items;
}

/* ============================================================================
 * insertSLL
 * ----------------------------------------------------------------------------
 * Inserts a value into the list at the user's specified index.
 *
 * items: The list to which insert the data.
 * index: The index at which to insert the data.
 * value: The data to insert.
 *
 * returns: void.
 * ============================================================================
*/
void insertSLL(sll *items, int index, void *value) {
	// In the case that the list is empty (items->size == 0):
	if((items->size == 0) && (index == 0)) {
		// Allocate memory for the node to be inserted into the list,
		// and point the list's head and tail node pointers to the newly
		// constructed node.
		items->head = malloc(sizeof(sllnode));
		items->tail = items->head;
		// Set the node's values.
		items->head->value = value;
		items->head->next = 0;
		// Increment the size of the list by 1 (to 1).
		++items->size;
	// In the case that the list is non-empty:
	} else if(items->size > 0) {
		// If data is to be inserted at the head of the list:
		if(index == 0) {
			// Allocate memory for a new node and set its member's data.
			sllnode *newnode = malloc(sizeof(sllnode));
			newnode->value = value;
			newnode->next = items->head;
			// Move the list's head pointer to the newnode, making it the
			// new head.
			items->head = newnode;
			// Increment the size of the list.
			++items->size;
		// If data is to be inserted at the tail of the list:
		} else if(index == items->size) {
			// Allocate memory for a new node and set its member's data.
			sllnode *newnode = malloc(sizeof(sllnode));
			newnode->value = value;
			newnode->next = 0;
			// Set the current tail's next pointer to the new node, and set
			// the tail pointer to the new node.
			items->tail->next = newnode;
			items->tail = newnode;
			// Increment the size of the list.
			++items->size;
		// If data is to be inserted someplace in the middle of the list:
		} else {
			// Allocate memory for a new node and set its member's data.
			sllnode *newnode = malloc(sizeof(sllnode));
			newnode->value = value;
			// Create a tracking node pointer and counter.
			sllnode *spot = items->head;
			int counter = 0;
			// Loop to the node just before the insert index.
			while(counter < index - 1) {
				spot = spot->next;
				++counter;
			}
			// Set the new node's next pointer to the next pointer
			// of the spot placeholder pointer.
			newnode->next = spot->next;
			// Set the spot pointer's next pointer to the new node.
			spot->next = newnode;
			// Increment the size of the list.
			++items->size;
		}
	}
}

/* ============================================================================
 * removeSLL
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
void *removeSLL(sll *items, int index) {
	// If removing data from the front (head) of the list:
	if(index == 0) {
		// Save the return value.
		void *value = items->head->value;
		// Create a temporary pointer node to point at
		// the current head, and move the head pointer to the head
		// pointer's next pointer.
		sllnode *temp = items->head;
		items->head = items->head->next;
		// Free the old head.
		free(temp);

		--items->size;
		return value;
	// If removing from the back (tail) of the list:
	} else if(index == items->size - 1) {
		// Save the return value.
		void *value = items->tail->value;
		// Create a temporary node pointer to point at the current tail,
		// and create a placeholder node pointer and associated counter.
		sllnode *temp = items->tail;
		sllnode *spot = items->head;
		int counter = 0;
		// Advance the placeholder node pointer to the node before the
		// current tail.
		while(counter < items->size - 2) {
			spot = spot->next;
			++counter;
		}
		// Set the tail pointer to the placeholder pointer & set its
		// next value to null (0).
		items->tail = spot;
		items->tail->next = 0;
		// Free the old tail still pointed to by the temp node pointer.
		free(temp);

		--items->size;
		return value;
	// If removing from someplace in the middle of the list:
	} else {
		// Create a placeholder node pointer and associated counter.
		sllnode *spot = items->head;
		int counter = 0;
		// Advance to the node before current index node.
		while(counter < index - 1) {
			spot = spot->next;
			++counter;
		}
		// Save the value;
		void *value = spot->next->value;
		// Create a temporary node pointer to keep a reference to the
		// node needed to be deleted.
		sllnode *temp = spot->next;
		// Set the placeholder node pointer's next pointer to the next,
		// next node.
		spot->next = spot->next->next;
		// Free the old node still pointed to by the temp node pointer.
		free(temp);

		--items->size;
		return value;
	}
}

/* ============================================================================
 * unionSLL
 * ----------------------------------------------------------------------------
 * Joins two SLLs together.  The donor list is rendered empty after the
 * procedure.
 *
 * recipient: The list to which keep a reference to (the first part of the
 * 	   	    joined lists).
 * donor: The list to which join to the tail of the recipient list (the second
 * 		part of the joined lists.)
 *
 * returns: void.
 * ============================================================================
*/
void unionSLL(sll *recipient, sll *donor) {
	if(donor->size == 0) {
		return;
	} else if(recipient->size == 0) {
		recipient->head = donor->head;
		recipient->tail = donor->tail;
		recipient->size = donor->size;
		donor->head = donor->tail = 0;
		donor->size = 0;
		return;
	} else {
		// Make the recipient's tail's next pointer point to
		// thead head of the donor list.
	    	recipient->tail->next = donor->head;
	    	// Change the recipient's tail pointer to the
	    	// donor's tail pointer.
	    	recipient->tail = donor->tail;
	    	// Add the donor's size to the recipient's size
	    	recipient->size += donor->size;
	    	// Make the donor list an empty list.
	    	donor->head = donor->tail = 0;
	    	donor->size = 0;
    	}
}

/* ============================================================================
 * getSLL
 * ----------------------------------------------------------------------------
 * Returns the data stored at a given index in the list.
 *
 * items: The list to which extract data from.
 * index: The index at which to extract data.
 *
 * returns: The data stored at the given 0-based index of the list.
 * ============================================================================
*/
void *getSLL(sll *items, int index) {
	// If getting from the head.
	if(index == 0) {
		return items->head->value;
	// If getting from the tail.
	} else if(index == (sizeSLL(items) - 1)) {
		return items->tail->value;
	// If getting form somewhere in the middle.
	} else {
		// Create a placeholder node pointer and associated counter.
		sllnode *spot = items->head;
		int counter = 0;
		// Advance to the desired index.
		while(counter < index) {
			spot = spot->next;
			++counter;
		}
		// Return the data stored at the desired index.
		return spot->value;
	}
}

/* ============================================================================
 * sizeSLL
 * ----------------------------------------------------------------------------
 * Returns the current size of a SLL.
 *
 * items: The list of which to determine the size.
 *
 * returns: The items->size member of the given list.
 * ============================================================================
*/
int sizeSLL(sll *items) {
    return items->size;
}

/* ============================================================================
 * displaySLL
 * ----------------------------------------------------------------------------
 * Displays the contents of a SLL in a [x1,x2,x3,...,xN] style.
 *
 * fp: The file (generally stdout) to which write the list.
 * items: The list to write out.
 *
 * returns: void.
 * ============================================================================
*/
void displaySLL(FILE *fp, sll *items) {
	// If the list is empty, print an empty list.
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
		sllnode *spot = items->head;
		while(1) {
			items->display(fp, spot->value);
			if(spot->next == 0) {
				break;
			} else {
				fprintf(fp, ",");
				spot = spot->next;
			}
		}
		fprintf(fp, "]");
	}
}

// EOF
