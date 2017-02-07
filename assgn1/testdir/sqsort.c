#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "comparator.h"
#include "queue.h"
#include "stack.h"
#include "reader.h"

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

int sort(queue *input, queue *output, stack *middle) {
     int stackUsed = 0; // bool
     void *lastValEnqueued = NULL;
     while(sizeQueue(input)) {
          // empty stack
          if(!sizeStack(middle)) {
               void *val = dequeue(input);
               // input queue is not NOT empty after getting element
               if(sizeQueue(input)) {
                    int compRes = comp(val, peekQueue(input));
                    // dequeued val is less than or equal to the next val
                    if(compRes <= 0) {
                         enqueue(output, val);
                         lastValEnqueued = val;
                         continue;
                    // dequeued val is greater than the next val
                    } else {
                         push(middle, val);
                         stackUsed = 1;
                         continue;
                    }
               // input queue is now EMPTY after getting element
               } else {
                    enqueue(output, val);
                    continue;
               }
          // Stack is not empty.
          } else {
               // If the value on top of the stack is less than/= the next value
               // on the input queue and greater than/= the last value
               // enqueued on the output queue, move top stack to output
               if(comp(peekStack(middle), peekQueue(input)) <= 0 &&
                         comp(peekStack(middle), lastValEnqueued) >= 0) {
                    void *val = pop(middle);
                    enqueue(output, val);
                    lastValEnqueued = val;
                    continue;
               } else {

                    void *val = dequeue(input);
                    // input queue is not NOT empty after getting element
                    if(sizeQueue(input)) {
                         int compRes = comp(val, peekQueue(input));
                         // dequeued val is less than or equal to the next val
                         if(compRes <= 0) {
                              enqueue(output, val);
                              lastValEnqueued = val;
                              continue;
                         // dequeued val is greater than the next val
                         } else {
                              push(middle, val);
                              stackUsed = 1;
                              continue;
                         }
                    // input queue is now EMPTY after getting element
                    } else {
                         enqueue(output, val);
                         continue;
                    }
               }
          }
          displayQueue(stdout, input);
          printf(" -> "); displayQueue(stdout, output);
          printf(" | "); displayStack(stdout, middle); printf("\n");
     }
     // move extra stack items over to output
     while(sizeStack(middle)) {
          enqueue(output, pop(middle));
     }
     unionQueue(input, output);

     return stackUsed;
}

int main(int argc, char **argv) {
     const char valid_args[4][3] = {"-v", "-d", "-r", "-s"};
     if(argc < 2) { printf("Too few arguments.\n"); exit(1); }

     // -v
     if(!strcmp(argv[1], valid_args[0])) {
          printf("Matthew D. Morgan\n");
          exit(0);
     // [-d, -r, -s]
     } else {
          switch(argv[1][1]) {
               case 'd':
                    comp = intComparator;
                    print = displayInteger;
                    read = readIntegers;
                    break;
               case 'r':
                    comp = realComparator;
                    print = displayReal;
                    read = readReals;
                    break;
               case 's':
                    comp = stringComparator;
                    print = displayString;
                    read = readStrings;
                    break;
               default:
                    printf("unknown flag '%c', valid flags are -d, -r, -s, and -v\n", argv[1][1]);
                    exit(1);
          }
     }

     queue *input = newQueue(print);
     queue *output = newQueue(print);
     stack *middle = newStack(print);

     if(argc == 2) {
          read(stdin, input);
     } else if(argc == 3) {
          FILE *fp = fopen(argv[2], "r");
          read(fp, input);
          fclose(fp);
     } else {
          printf("Too many arguments.\n");
     }

     displayQueue(stdout, input); printf("\n");
     int ret = sort(input, output, middle);
     while(ret == 1) {
          displayQueue(stdout, input); printf("\n");
          ret = sort(input, output, middle);
     }
     displayQueue(stdout, input); printf("\n");
     return 0;
}
