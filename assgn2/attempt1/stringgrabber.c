#include "stringgrabber.h"

// Fatal is written in bstrees.c.  It isn't used in this module, but it is
// included in case it's needed in the future.
extern void Fatal(char *,...);

/* This function was inspired/modified from a Stack
   overflow post pointed out to me by another student.
   It removes all punctuation and digits from a string,
   converts uppercase characters to lowercase, and
   shortens spans of whitespace characters into a single
   space. It does not allocate or deallocate memory.
 */
void cleanString(char *s) {
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
          } else if(!isalpha(s[i])) {
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

/* This function reads a token or a string from a file and returns
   a new string * object created from the token or string read from
   the file. It cleans the string by calling cleanString. If the
   file is empty or the cleaned string is empty, it returns null.
*/
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
