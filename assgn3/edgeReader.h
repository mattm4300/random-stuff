#ifndef __INFO_GATHER__H
#define __INFO_GATHER__H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scanner.h"

typedef struct edgeDefinition {
     int verta;
     int vertb;
     int weight;
} edgeDefinition;

extern edgeDefinition *readDefinition(FILE *);
extern int largestVertex(char *);
extern void populateMatrix(int **, char *);

#endif
