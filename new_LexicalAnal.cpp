#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isInteger(char* s) { 
  int len = strlen(s);

  char integerArray[] = "0123456789";
  int isNotADigit = 0;

  for (int i = 0 ; i < len; i++) {
    for (int j = 0 ; j < 10; j++) {
      if (s[i] != integerArray[j]) {
        isNotADigit = 1;
      }
      if (isNotADigit || (s[i] == '-' && i > 0) || len == 0) {
        return 0;
      }
    }
  }

  return 1;
}

int isDelimiter(char ch) { 
  char delimiterArray[] = " +-*/,;><=()[]{}";
  for (int i = 0; i < 16; i++) {
    if (ch == delimiterArray[i]) {
      return 1;
    }
  }
  return 0;
}

int isValidIdentifier(char* s) { 
  char identiferArray[] = "0123456789";
  for (int i = 0; i < 10; i++) {
    if (s[0] == identiferArray[i]) {
      return 0;
    }
  }
  return 1; 
}

int isOperator(char ch) { 
  char operatorArray[] = "+-*/><=";
  for (int i = 0 ; i < 6; i++) {
    if (ch == operatorArray[i]) {
      return 1;
    }
  }
  return 0; 
} 

int isKeyword(char* s) {
  char keywords[32][10] = {
    "auto", "double", "int", "struct", "break", "else", "long",
    "switch" ,"case" ,"enum" ,"register" ,"typedef" ,"char",
    "extern" ,"return" ,"union" ,"const" ,"float" ,"short",
    "unsigned" ,"continue" ,"for" ,"signed" ,"void" ,"default",
    "goto" ,"sizeof" ,"volatile" ,"do" ,"if" ,"static" ,"while"
   };
  for (int i = 0; i < 32; i++) {
    if (!strcmp(s, keywords[i])) {
      return 1;
    }
  }
  return 0;
}

char* subString(char* s, int l, int r) { 
  char* subStr = (char*)malloc(sizeof(char) * (r - l + 2));

  for (int i = l; i <= r; i++) {
    subStr[i - l] = s[i];
  }

  subStr[r - l + 1] = '\0'; 
  return subStr; 
} 

void parse(char *s) {
  int l = 0, r = 0;
  int len = strlen(s);
  while (r <= len && l <= r) {
    if (!isDelimiter(s[r])) {
      r++;
    }
    if (isDelimiter(s[r]) && l == r) {
      if (isOperator(s[r])) {
        printf("%c -> validOperator\n", s[r]);
      }
      l = ++r;
    } else if ((isDelimiter(s[r]) || r == len) && l != r) {
          char *subStr = subString(s, l, r - 1);
          if (isKeyword(subStr)) {
            printf("%s -> keyword\n", subStr);
          } else if (isInteger(subStr)) {
            printf("%s -> integer\n", subStr);
          } else if (isValidIdentifier(subStr) && !isDelimiter(s[r - 1])) {
            printf("%s -> aValidIdentifier\n", subStr);
          } else if (!isValidIdentifier(subStr) && !isDelimiter(s[r - 1])) {
            printf("%s -> notAValidIdentifier\n", subStr);
          }
          l = r;
    }
  }
}

int main() {
  char* buffer = (char*)malloc(sizeof(char));
  printf("Enter a C style statement or code\n>>> ");
  scanf("%[^\n]", buffer);
  parse(buffer);
  puts("-------------------");
}