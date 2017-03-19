#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void) {
     char *a = "ó";
     int i;
     printf("<%s> | len: %d\n", a, (int) strlen(a));
     for(i = 0; i < (int) strlen(a); i++) {
          printf("<%c> ", a[i]);
          printf("%d\n", isalpha(a[i]));
     }
     return 0;
}
