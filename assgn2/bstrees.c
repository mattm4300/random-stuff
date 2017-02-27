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
     printf("attempting to delete all:\n");
     int i;
     for(i = 97; i <= 122; i++) {
          char ch[2]; ch[0] = (char) i; ch[1] = '\0';
          printf("Attempting to find and delete <%s>\n", ch);
          bstNode *p = findBSTNode(tree, newString(ch));
          if(p) {
               printf("<%s> found\n", ch);
               p = swapToLeafBSTNode(p);
               pruneBSTNode(p);
               printf("<%s> deleted\n", ch);
          }
          displayBST(stdout, tree);
     }
     displayBST(stdout, tree);
     printf("done.\n");
     return 0;
}
