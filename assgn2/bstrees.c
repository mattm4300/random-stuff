#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "bst.h"
#include "comparator.h"
#include "string.h"
#include "real.h"
#include "integer.h"
#include "stringgrabber.h"

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

int main(int argc, const char **argv) {
     FILE *fp = fopen(argv[1], "r");
     bst *mytree = newBST(displayString, stringComparator);
     string *str = grabString(fp);
     while(1) {
          if(feof(fp)) break;
          if(str != 0) {
               printf("Word read: "); displayString(stdout, str); printf("\n");
               if(!findBST(mytree, str)) {
                    printf("attempting insert.\n");
                    insertBST(mytree, str);
                    printf("insert successfull\n");
               }

          }
          str = grabString(fp);
     }
     fclose(fp);
     displayBST(stdout, mytree);
     printf("done.\n");
     return 0;
}
