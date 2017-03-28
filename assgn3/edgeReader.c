#include <stdio.h>
#include <stdlib.h>
#include "edgeReader.h"

edgeDefinition *readDefinition(FILE *fp) {
     // Make sure there's another definition to read.
     char x = readChar(fp);
     if(x == EOF) return NULL;
     // Make sure to put that char back!
     ungetc(x, fp);
     // There exists another definition, so continue onward.
     edgeDefinition *ed = malloc(sizeof(edgeDefinition));
     ed->verta = readInt(fp);
     ed->vertb = readInt(fp);
     char *token = readToken(fp);
     // No weight defined.
     if(!strcmp(token, ";")) {
          ed->weight = 1;
     // Weight defined.
     } else {
          ed->weight = atoi(token);
          // Get rid of the left over semi-colon.
          free(token);
          token = readToken(fp);
     }
     free(token);
     return ed;
}

int largestVertex(char *fileName) {
     FILE *fp = fopen(fileName, "r");
     int lv = -1;
     edgeDefinition *ed;
     while(1) {
          ed = readDefinition(fp);
          if(ed == NULL) break;
          if(ed->verta > lv) lv = ed->verta;
          if(ed->vertb > lv) lv = ed->vertb;
          free(ed);
     }
     fclose(fp);
     return lv;
}

/* Helper function for populateMatrix. This func will handle edge assignments.
(1) reassignments (if smaller edge weight given the original is overwritten)
(2) x, y = y, x, so account for that.
*/
static void placeEdge(int **mat, edgeDefinition *ed) {
     int x = ed->verta;
     int y = ed->vertb;
     // Our graphs are simple, so a vertex won't have an edge to itself.
     // Therefore, skip if edge is a self-referencing edge.
     if(x == y) return;
     // x, y and y, x have not been set yet-- set both.
     if(mat[x][y] == INT_MAX) mat[x][y] = mat[y][x] = ed->weight;
     // x, y & y, x have been set, but see if new weight is smaller.
     // Replace if so.
     else if(ed->weight < mat[x][y]) mat[x][y] = mat[y][x] = ed->weight;
     return;
}

void populateMatrix(int **mat, char *fileName) {
     FILE *fp = fopen(fileName, "r");
     edgeDefinition *ed;
     while(1) {
          ed = readDefinition(fp);
          if(ed == NULL) break;
          placeEdge(mat, ed);
          free(ed);
     }
     fclose(fp);
     return;
}
