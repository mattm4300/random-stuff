#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "vertex.h"

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

void dispayVert(FILE *fp, void *val) {
     Vertex *v = (Vertex *) val;
     fprintf(fp, "%d", v->value);
     return;
}

Vertex *newVertex(int vert) {
     Vertex *new = malloc(sizeof(Vertex));
     new->value = vert;
     new->neighbors = newDArray(displayInteger);
     new->distance = INT_MAX;
     new->steps = 0;
     new->bnode = NULL;
     return new;
}

Neighbor *newNeighbor(int vert, int weight) {
     Neighbor *n = malloc(sizeof(Neighbor));
     n->vert = newVertex(vert);
     n->weight = weight;
     return n;
}

Vertex *vertInList(DArray *list, int vert) {
     int index = 0;
     for(index = 0; index < sizeDArray(list); index++) {
          Vertex *v = getDArray(list, index);
          if(v->value == vert) {
               return v;
          }
     }
     return NULL;
}

Neighbor * neighborInList(DArray *list, int vert) {
     int index = 0;
     for(index = 0; index < sizeDArray(list); index++) {
          Neighbor *n = getDArray(list, index);
          if(n->vert->value == vert) {
               return n;
          }
     }
     return NULL;
}

void insertVertex(DArray *list, int a, int b, int w) {
     Vertex *v = vertInList(list, a);
     // vert a isn't already in big vertex list.
     if(v == NULL) {
          v = newVertex(a);
          Neighbor *n = newNeighbor(b, w);
          insertDArray(v->neighbors, n);
          insertDArray(list, v);
     // vert a is already in big vertex list.
     } else {
          Neighbor *n = neighborInList(v->neighbors, b);
          // n isn't in the vertex's neighbor list.
          if(n == NULL) {
               n = newNeighbor(b, w);
               insertDArray(v->neighbors, n);
          } else {
               // If neighbor already exists, but the new weight is smaller!
               if(w < n->weight) {
                    n->weight = w;
               }
          }
     }
}

void fillAdjList(DArray *list, FILE *fp) {
     edgeDefinition *ed = readDefinition(fp);
     while(ed != NULL) {
          // do a to b
          insertVertex(list, ed->verta, ed->vertb, ed->weight);
          // do b to a
          insertVertex(list, ed->vertb, ed->verta, ed->weight);
          // Free ed.
          free(ed);
          // Grab the next definition.
          ed = readDefinition(fp);
     }
}

void debugList(FILE *fp, DArray *list) {
     int a, b;
     for(a = 0; a < sizeDArray(list); a++) {
          Vertex *v = getDArray(list, a);
          fprintf(fp, "%d: ", v->value);
          for(b = 0; b < sizeDArray(v->neighbors); b++) {
               Neighbor *n = getDArray(v->neighbors, b);
               fprintf(fp, "%d(%d)", n->vert->value, n->weight);
               if((sizeDArray(v->neighbors) - b) > 1) {
                    fprintf(fp, "->");
               }
          }
          fprintf(fp, "\n");
     }
}

int compareVertex(void *a, void *b) {
     if(a == NULL && b == NULL) return 0;
     else if(a == NULL) return -1;
     else if(b == NULL) return 1;

     Vertex *x = (Vertex *) a;
     Vertex *y = (Vertex *) b;
     if(x->value == y->value) return 0;
     else if(x->value < y->value) return -1;
     else return 1;

}



Vertex *getMinVertex(DArray *a) {
     if(sizeDArray(a) == 0) return NULL;

     int i = 0;
     Vertex *min = (Vertex *) getDArray(a, 0);
     for(i = 1; i < sizeDArray(a); i++) {
          Vertex *spot = getDArray(a, i);
          if(spot->value < min->value) {
               min = spot;
          }
     }
     return min;
}
