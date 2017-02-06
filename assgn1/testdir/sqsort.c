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

     


     return 0;
}
