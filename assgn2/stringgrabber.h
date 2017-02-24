#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "string.h"
#include "scanner.h"

#ifndef _STRINGGRABBER__H_
#define _STRINGGRABBER__H_

extern char cleanChar(char);
extern void addCharToString(char *, size_t *, char);
extern string *grabString(FILE *);

#endif
