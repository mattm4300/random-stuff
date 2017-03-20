#include "darray.h"

typedef struct DArray {
    void **array; //an array of void pointers
    int capacity; //total number of slots
    int size; //number of filled slots
    void (*display)(FILE *,void *);
} DArray;

DArray *newDArray(void (*display)(FILE *, void *)) {
     DArray *a = malloc(sizeof(DArray));
     a->array = malloc(sizeof(void *) * 1);
     a->capacity = 1;
     a->size = 0;
     a->display = display;
     return a;
}

void insertDArray(DArray *a, void *v) {
     // Array full, so double array cap.
     if(a->size == a->capacity) {
          a->array = realloc(a->array, sizeof(void *) * a->capacity * 2);
          a->capacity *= 2;
     }
     a->array[a->size++] = v;
}

void *removeDArray(DArray *a) {
     // If array empty, return null?
     if(a->size == 0) return NULL;

     // Remove the value.
     void *retVal = a->array[a->size - 1];
     a->array[a->size - 1] = NULL;
     --a->size;

     // Resize array if necessary.
     if((double) a->size <= ((double) a->capacity / 4.0)) {
          a->array = realloc(a->array, sizeof(void *) * (a->capacity / 2));
          a->capacity /= 2;
     }

     return retVal;
}

void *getDArray(DArray *a, int index) {
     return a->array[index];
}

void setDArray(DArray *a, int index, void *value) {
     // If index is the size of the array, call insertDArray instead.
     if(index == a->size) return insertDArray(a, value);
     else a->array[index] = value;
}

int sizeDArray(DArray *a) { return a->size; }

void displayDArray(FILE *fp, DArray *a) {
     // Print the array.
     int index = 0;
     fprintf(fp, "[");
     while(index < a->size) {
          a->display(fp, a->array[index]);
          if(index + 1 < a->size) fprintf(fp, ",");
          ++index;
     }
     fprintf(fp, "]");
     // Print the extra spaces.
     fprintf(fp, "[%d]", a->capacity - a->size);
}
