#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "bst.h"
#include "vbst.h"
#include "comparator.h"
#include "string.h"
#include "real.h"
#include "integer.h"
#include "stringgrabber.h"
#include "queue.h"

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

void readCorpus(bst *tree, FILE *fp) {
     string *str = grabString(fp);
     while(str != NULL || !feof(fp)) {
          if(str != NULL && !findBST(tree, str)) {
               insertBST(tree, str);
          }
          str = grabString(fp);
     }
}

int main(int argc, char **argv) {
     FILE *fp = fopen(argv[1], "r");
     bst *tree = newBST(displayString, stringComparator);
     readCorpus(tree, fp);
     fclose(fp);
     displayBST(stdout, tree);
     statisticsBST(tree, stdout); printf("\n");
     bstNode *n = findBSTNode(tree, newString("f"));
     if(n != NULL) {
          n = swapToLeafBSTNode(n);
          pruneBSTNode(tree, n);
     }
     displayBST(stdout, tree);
     printf("stats:\n");
     statisticsBST(tree, stdout);
     printf("done.\n");
     return 0;
}
