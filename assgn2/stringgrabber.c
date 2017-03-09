#include "stringgrabber.h"

extern void Fatal(char *,...);

/*
static char cleanChar(char ch) {
     if(ch >= 65 && ch <= 90) {
          return (char)(ch + 32);
     } else if(ch >= 97 && ch <= 122) {
          return ch;
     } else {
          return 0;
     }
}

static int isValid(char ch) {
     return cleanChar(ch);
}

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

/* This function was inspired/modified from a Stack
 overflow post pointed out to me by another student. */
static void cleanString(char *s) {
     int i = 0;
     int j = 0;
     // Loop until we hit the null character in the string.
     while(s[i] != '\0') {
          // We need to handle spaces.
          if(isspace(s[i])) {
               // Skip all the whitespace AND invalid chars here.
               while(isspace(s[i]) || ispunct(s[i]) || isdigit(s[i])) {
                    ++i;
               }
               // We skipped a bunch of spaces and/or invalid chars, so just
               // leave a single space char.
               s[j] = ' ';
               ++j;
          // If we encounter a punct or digit simply skip over it.
          } else if(ispunct(s[i]) || isdigit(s[i])) {
               ++i;
          // If char is uppercase, make it lowercase.
          } else if(isupper(s[i])) {
               s[j] = tolower(s[i]);
               ++j;
               ++i;
          // If i and j are in the same spot, increment them.
          } else if(i == j) {
               ++i;
               ++j;
          // Copy the character.
          } else {
               s[j] = s[i];
               ++j;
               ++i;
          }
     }
     // Set the last spot we're in to the null char.
     s[j] = '\0';
}

string *grabString(FILE *fp) {
     char *s;
     if(stringPending(fp)) {
          s = readString(fp);
          // EOF
          if(s == NULL) return NULL;
          cleanString(s);
          if(!strcmp("", s)) return NULL;
          else return newString(s);
     } else {
          s = readToken(fp);
          // EOF
          if(s == NULL) return NULL;
          cleanString(s);
          if(!strcmp("", s)) return NULL;
          else return newString(s);
     }
}
