#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isInteger(char* str) { 
  int i, len = strlen(str); 
  if (len == 0) {
    return 0;
  } 
  for (i = 0; i < len; i++) { 
    if (str[i] != '0' && str[i] != '1' && str[i] != '2'
      && str[i] != '3' && str[i] != '4' && str[i] != '5'
      && str[i] != '6' && str[i] != '7' && str[i] != '8'
      && str[i] != '9' || (str[i] == '-' && i > 0)) {
      return 0;
    } 
  }
  return 1;
}

int isRealNumber(char* str) {
  int i, len = strlen(str); 
  int hasDecimal = 0;
  if (len == 0) {
    return 0;
  } 
  for (i = 0; i < len; i++) { 
    if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5'
      && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0)) {
      return 0;
    } 
    if (str[i] == '.') {
      hasDecimal = 1; 
    }
  } 
  return hasDecimal;
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

int validIdentifier(char* str) { 
  char identiferArray[] = "0123456789";
  for (int i = 0; i < 10; i++) {
    if (str[0] == identiferArray[i]) {
      return 0;
    }
  }
  return 1; 
}

int isOperator(char ch) { 
  if (ch == '+' || ch == '-' || ch == '*' ||  ch == '/' || ch == '>' || ch == '<' ||  ch == '=') {
    return 1;
  }   
  return 0; 
} 

int isKeyword(char* str) {
  char keywords[32][10] = {
    "auto", "double", "int", "struct", "break", "else", "long",
    "switch" ,"case" ,"enum" ,"register" ,"typedef" ,"char",
    "extern" ,"return" ,"union" ,"const" ,"float" ,"short",
    "unsigned" ,"continue" ,"for" ,"signed" ,"void" ,"default",
    "goto" ,"sizeof" ,"volatile" ,"do" ,"if" ,"static" ,"while"
   };
  for (int i = 0; i < 32; i++) {
    if (!strcmp((const char*)str, keywords[i])) {
      return 1;
    }
  }
  return 0;
}

char* subString(char* str, int left, int right) { 
  char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));
  for (int i = left; i <= right; i++) {
    subStr[i - left] = str[i];
  }
  subStr[right - left + 1] = '\0'; 
  return subStr; 
} 

void parse(char *str) {
  int left = 0, right = 0;
  int len = strlen(str);
  // loop to parse string
  while (right <= len && left <= right) {
    if (!isDelimiter(str[right])) {
      right++;
    }
    if (isDelimiter(str[right]) && left == right) {
      if (isOperator(str[right])) {
        printf("%c -> OPERATOR\n", str[right]);
      }
      right++;
      left = right;
    } else if (isDelimiter(str[right]) && left != right || (right == len && left != right)) {
      char *subStr = subString(str, left, right - 1);
      if (isKeyword(subStr)) {
        printf("%s -> KEYWORD\n", subStr);
      } else if (isInteger(subStr)) {
        printf("%s -> INTEGER\n", subStr);
      } else if (isRealNumber(subStr)) {
        printf("%s -> REAL_NUMBER\n", subStr);
      } else if (validIdentifier(subStr) && !isDelimiter(str[right - 1])) {
        printf("%s -> VALID_IDENTIFIER\n", subStr);
      } else if (!validIdentifier(subStr) && !isDelimiter(str[right - 1])) {
        printf("%s -> NOT_A_VALID_IDENTIFIER\n", subStr);
      }
      left = right;
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