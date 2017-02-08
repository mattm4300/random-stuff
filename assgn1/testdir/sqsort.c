/* =======================================================================
 * FILENAME: sqsort.c
 *
 * AUTHOR: Matthew Morgan, mdmorgan1@crimson.ua.edu
 *
 * DESCRIPTION:
 *   Contains an implementation for a sorting algorithm using two queues
 *   and a stack.
 *
 * NOTES:
 *
 *
 * LEGAL:
 *   This program is the top program of my "program tree", which are all
 *   the files I use in order to compile and execute my sorting algorithm.
 *
 *   In my program tree, I use integer.c, integer.h, scanner.c, and
 *   scanner.h. These files were published by Dr. Lusth (University of
 *   Alabama) for free distribution, modificatin, and use.
 *
 *   I have not modified any files provided by Dr. Lusth, they are all
 *   used as published.
 *
 *
 * VERSION 1.0
 * =======================================================================
 */

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
     while(sizeQueue(input)) {
          /*displayQueue(stdout, input); printf(" -> ");
          displayQueue(stdout, output); printf("\ns: ");
          displayStack(stdout, middle); printf("\n");*/
          // stack isn't empty.
          if(sizeStack(middle)) {
               // if stack top > queue front, move stack top to output
               if(comp(peekStack(middle), peekQueue(input)) > 0) {
                    enqueue(output, pop(middle));
               // if stack top == queue front, move stack top to output.
               } else if(comp(peekStack(middle), peekQueue(input)) == 0) {
                    enqueue(output, pop(middle));
               // input queue front is > stack top
               } else if(comp(peekStack(middle), peekQueue(input)) < 0) {
                    void *val = dequeue(input);
                    // if the input queue is not empty after getting a value off
                    if(sizeQueue(input)) {
                         // if the dequeued value is >= the next value
                         // move to output queue
                         if(comp(val, peekQueue(input)) >= 0) {
                              enqueue(output, val);
                         // if the dequeued value is < the next value, move
                         // to the stack
                         } else {
                              push(middle, val);
                              stackUsed = 1;
                         }
                    // if the input queue IS empty after getting a value off,
                    // push to output queue
                    } else {
                         enqueue(output, val);
                    }
               }
          // stack is empty
          } else {
               void *val = dequeue(input);
               // if the input queue is not empty after getting a value off
               if(sizeQueue(input)) {
                    // if the dequeued value is >= the next value
                    // move to output queue
                    if(comp(val, peekQueue(input)) >= 0) {
                         enqueue(output, val);
                    // if the dequeued value is < the next value, move
                    // to the stack
                    } else {
                         push(middle, val);
                         stackUsed = 1;
                    }
               // if the input queue IS empty after getting a value off,
               // push to output queue
               } else {
                    enqueue(output, val);
               }
          }
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

     int passes = 0;

     displayQueue(stdout, input); printf("\n");
     int ret = sort(input, output, middle);
     while(ret == 1) {
          ++passes;
          displayQueue(stdout, input); printf("\n");
          ret = sort(input, output, middle);
     }
     if(passes == 0) {
          displayQueue(stdout, input); printf("\n");
     }
     return 0;
}
