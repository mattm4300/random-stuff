#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "bst.h"
#include "vbst.h"
#include "rbt.h"
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

void readCorpusBST(bst *tree, FILE *fp) {
     string *str = grabString(fp);
     while(str != NULL || !feof(fp)) {
          if(str != NULL && !findBST(tree, str)) {
               insertBST(tree, str);
          }
          str = grabString(fp);
     }
}

void readCorpusVBST(vbst *tree, FILE *fp) {
     string *str = grabString(fp);
     while(str != NULL || !feof(fp)) {
          if(str != NULL) {
               insertVBST(tree, str);
          }
          str = grabString(fp);
     }
}

void readCorpsRBT(rbt *tree, FILE *fp) {
     string *str = grabString(fp);
     while(str != NULL || !feof(fp)) {
          if(str != NULL) {
               displayString(stdout, str); printf("\n");
               insertRBT(tree, str);
          }
          str = grabString(fp);
     }
}

void readCommands(queue *q, FILE *fp) {
     string *str = grabString(fp);
     while(str != NULL || !feof(fp)) {
          if(str == NULL) {
               enqueue(q, NULL);
          } else {
               enqueue(q, str);
          }
          str = grabString(fp);
     }
}

int main(int argc, char **argv) {
     if(argc != 4 && argc != 5) {
          fprintf(stderr, "Invalid # of command arguments.\n");
          exit(-1);
     }
     // Gather and process command-line args.
     char treeType = argv[1][1];
     FILE *corpus = fopen(argv[2], "r");
     FILE *commands = fopen(argv[3], "r");
     FILE *output;
     if(argc == 5) output = fopen(argv[4], "w");
     else output = stdout;
     // Get the commands.
     queue *q = newQueue(displayString);
     readCommands(q, commands);
     // Read the corpus.
     void *tree = NULL;
     switch(treeType) {
          case 'v': {
               tree = (vbst *) newVBST(displayString, stringComparator);
               readCorpusVBST(tree, corpus);
               break;
          } case 'r':
               tree = (rbt *) newRBT(displayString, stringComparator);
               readCorpsRBT(tree, corpus);
               break;
          default: {
               tree = (bst *) newBST(displayString, stringComparator);
               readCorpusBST(tree, corpus);
               break;
          }
     }
     // Execute commands.
     if(treeType == 'v') {
          while(sizeQueue(q)) {
               char command = getString(dequeue(q))[0];
               switch(command) {
                    case 'i': {
                         string *str = dequeue(q);
                         if(str == NULL) break;
                         insertVBST(tree, str);
                         break;
                    } case 'd': {
                         string *str = dequeue(q);
                         int n = findVBST(tree, str);
                         if(n == 0) {
                              fprintf(stderr, "Value ");
                              displayString(stderr, str);
                              fprintf(stderr, " not found.\n");
                              break;
                         }
                         deleteVBST(tree, str);
                         break;
                    } case 'f': {
                         string *str = dequeue(q);
                         fprintf(output, "Frequency of \"%s\": %d\n",
                              getString(str), findVBST(tree, str));
                         break;
                    } case 's': {
                         displayVBST(output, tree);
                         break;
                    } case 'r': {
                         statisticsVBST(tree, output);
                         break;
                    }
               }
          }
     } else if(treeType == 'r') {
          while(sizeQueue(q)) {
               char command = getString(dequeue(q))[0];
               switch (command) {
                    case 'i': {
                         string *str = dequeue(q);
                         if(str == NULL) break;
                         insertRBT(tree, str);
                         break;
                    } case 'd': {
                         // We're not implementing delete, so just toss the
                         // value that would be deleted.
                         string *str = dequeue(q);
                         // Suppress compiler warning for used variable.
                         free(str);
                         break;
                    } case 'f': {
                         string *str = dequeue(q);
                         fprintf(output, "Frequency of \"%s\": %d\n",
                              getString(str), findRBT(tree, str));
                         break;
                    } case 's': {
                         displayRBT(output, tree);
                         break;
                    } case 'r': {
                         statisticsRBT(tree, output);
                         break;
                    }
               }
          }
     } else {
          while(sizeQueue(q)) {
               char command = getString(dequeue(q))[0];
               switch(command) {
                    case 'i': {
                         string *str = dequeue(q);
                         if(str == NULL) break;
                         insertBST(tree, str);
                         break;
                    } case 'd': {
                         string *str = dequeue(q);
                         bstNode *n = findBSTNode(tree, str);
                         if(n == NULL) {
                              fprintf(stderr, "Value ");
                              displayString(stderr, str);
                              fprintf(stderr, " not found.\n");
                              break;
                         }
                         n = swapToLeafBSTNode(n);
                         pruneBSTNode(tree, n);
                         break;
                    } case 'f': {
                         fprintf(stderr, "No tree type for base bst.\n");
                         break;
                    } case 's': {
                         displayBST(output, tree);
                         break;
                    } case 'r': {
                         statisticsBST(tree, output);
                         break;
                    }
               }
          }
     }
     // close files.
     fclose(corpus);
     fclose(commands);
     if(argc == 5) fclose(output);
     return 0;
}
