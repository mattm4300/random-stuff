#include "stringgrabber.h"

extern void Fatal(char *,...);

char cleanChar(char ch) {
     if(ch >= 97 && ch <= 122) {
          return ch;
     } else if(ch >= 65 && ch <= 90) {
          return (char) (ch + 32);
     } else {
          return 0;
     }
}

void addCharToString(char *str, size_t *currentSize, char ch) {
     str = realloc(str, *currentSize + 1);
     *currentSize += 1;
     str[*currentSize - 1] = '\0';
     str[*currentSize - 2] = ch;

}

string *grabString(FILE *fp) {
     // Setup.
     size_t *currentSize = malloc(sizeof(size_t));
     *currentSize = 1;
     char *str = malloc(*currentSize);
     strcpy(str, "");
     // Note the use of readChar, not readRawChar here to skip over
     // whitespace to the next non-whitespace character or EOF.
     char spot = readChar(fp);
     // EOF
     if(spot == -1) { return NULL; }
     // Token
     if(spot != '\"') {
          while(!isspace(spot) && spot != -1) {
               spot = cleanChar(spot);
               if(spot != 0) {
                    addCharToString(str, currentSize, spot);
               }
               spot = readRawChar(fp);
               if(isspace(spot)) break;
          }
     // String
     } else {
          char lastSpot = spot;
          // Toss the quotation mark.
          spot = readRawChar(fp);
          while(spot != '\"') {
               if(!isspace(spot)) {
                    spot = cleanChar(spot);
                    if(spot != 0) {
                         addCharToString(str, currentSize, spot);
                         lastSpot = spot;
                    }
                    spot = readRawChar(fp);
               } else if(isspace(spot) && !isspace(lastSpot)) {
                    addCharToString(str, currentSize, ' ');
                    lastSpot = ' ';
                    spot = readRawChar(fp);
               } else if(isspace(spot) && isspace(lastSpot)) {
                    spot = readRawChar(fp);
               }
          }
     }
     // If last thing read from file was quoted string, we probably read
     // an empty string now, so check for empty string.
     if(strlen(str) == 0) {
          free(str);
          free(currentSize);
          return NULL;
     }

     // Cleanup.
     string *retString = newString(str);
     free(str);
     free(currentSize);

     return retString;
}
