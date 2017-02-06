#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "string.h"

extern void Fatal(char *, ...);

string *newString(char *x) {
     string *p = malloc(sizeof(string));
     if(p == 0) { Fatal("out of memory\n"); }
     p->value = malloc(sizeof(strlen(x)));
     strcpy(p->value, x);
     return p;
}

char *getString(string *v) {
     return v->value;
}

char *setString(string *v, char *x) {
     char *old = malloc(sizeof(strlen(v->value)));
     strcpy(old, v->value);
     free(v->value);
     v->value = malloc(sizeof(strlen(x)));
     strcpy(v->value, x);
     return old;
}

void displayString(FILE *fp, void *v) {
     fprintf(fp, "\"%s\"", getString((string *) v));
}

int compareString(void *v, void *w) {
     return strcmp(((string *) v)->value, ((string *) w)->value);
}

void freeString(string *v) {
     free(v);
}
