#include "stringgrabber.h"

extern void Fatal(char *,...);

char cleanChar(char ch) {
     if(ch >= 65 && ch <= 90) {
          return (char)(ch + 32);
     } else if(ch >= 97 && ch <= 122) {
          return ch;
     } else {
          return 0;
     }
}

int isValid(char ch) {
     return cleanChar(ch);
}

/*
char *appendCharToString(char *str, char ch) {
     size_t currentSize = strlen(str);
     char *newStr = realloc(str, currentSize + 2);
     newStr[currentSize] = ch;
     newStr[currentSize + 1] = '\0';
     return newStr;
}

string *grabString(FILE *fp) {
     char *str = malloc(1);
     str[0] = '\0';
     char ch = readChar(fp);
     // If file empty.
     if(ch <= 0) {
          free(str);
          return NULL;
     }
     // Token
     if(ch != '\"') {
          while(!isspace(ch)) {
               ch = cleanChar(ch);
               if(isValid(ch)) {
                    str = appendCharToString(str, ch);
               }
               ch = readRawChar(fp);
          }
     // String
     } else {
          char lastCharAppended = ch;
          // Toss quotation mark.
          ch = readRawChar(fp);
          while(ch != '\"') {
               if(!isspace(ch)) {
                    if(isValid(ch)) {
                         ch = cleanChar(ch);
                         str = appendCharToString(str, ch);
                         lastCharAppended = ch;
                    }
               } else if(isspace(ch) && !isspace(lastCharAppended)) {
                    str = appendCharToString(str, ' ');
                    lastCharAppended = ' ';
               }
               ch = readRawChar(fp);
          }
     }
     // Make sure we're not returning an empty string.
     if(strcmp(str, "") == 0) {
          free(str);
          return NULL;
     }

     string *retString = newString(str);
     free(str);
     return retString;
}
*/

static void cleanString(char *s) {
     int i = 0;
     int j = 0;
     while(j < (int) strlen(s)) {
          if(isValid(s[j])) {
               s[i] = s[j];
               ++i; ++j;
          } else if(isspace(s[j])) {
               if(isspace(s[i])) {
                    ++j;
               } else {
                    s[i] = ' ';
                    ++i; ++j;
               }
          } else {
               ++j;
          }
     }
     s[i] = '\0';
}

string *grabString(FILE *fp) {
     char *s;
     if(stringPending(fp)) {
          s = readString(fp);
          cleanString(s);
          if(!strcmp("", s)) return NULL;
          else return newString(s);
     } else {
          s = readToken(fp);
          cleanString(s);
          if(!strcmp("", s)) return NULL;
          else return newString(s);
     }
}
