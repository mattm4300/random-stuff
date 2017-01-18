#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "sll.h"
#include "integer.h"

void
Fatal(char *fmt, ...)
    {
    va_list ap;

    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
    }


void diagnose_sll(sll *items) {
    printf("Head: %d\n", getInteger(items->head->value));
    printf("Tail: %d\n", getInteger(items->tail->value));
    printf("Size: %d\n", sizeSLL(items));
    displaySLL(stdout, items);
    printf("\n");
}

static void showItems(sll *items)
      {
      printf("The items are ");
      displaySLL(stdout,items);
      printf(".\n");
      }

 int main(void)
      {
      sll *items = newSLL(displayInteger);
      showItems(items);
      insertSLL(items,0,newInteger(3));                   //insert at front
      insertSLL(items,sizeSLL(items),newInteger(2));      //insert at back
      insertSLL(items,1,newInteger(1));                   //insert at middle
      showItems(items);
      printf("The value ");
      displayInteger(stdout,removeSLL(items,0));          //remove from front
      printf(" was removed.\n");
      showItems(items);
      int x = getInteger((integer *) getSLL(items,0));   //get the first item
      printf("The first item is %d.\n",x);
      return 0;
      }
