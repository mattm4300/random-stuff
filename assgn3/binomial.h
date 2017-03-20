#ifndef __BINHEAP_INCLUDED__
#define __BINHEAP_INCLUDED__

#include <stdio.h>
#include "darray.h"

typedef struct BinomialNode BinomialNode;

BinomialNode *newBinomialNode(void (*display)(FILE *,void *), void *value);
void displayBinomialNode(FILE *fp,void *n);

typedef struct Binomial Binomial;

extern Binomial *newBinomial(void (*d)(FILE *,void *), int (*c)(void *,void *), void (*u)(void *,BinomialNode *));
extern BinomialNode *insertBinomial(Binomial *b,void *value);
extern int sizeBinomial(Binomial *b);
extern void deleteBinomial(Binomial *b,BinomialNode *n);
extern void decreaseKeyBinomial(Binomial *b,BinomialNode *n,void *value);
extern void *extractBinomial(Binomial *b);
extern void displayBinomial(FILE *fp,Binomial *b);
#endif
