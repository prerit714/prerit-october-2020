// prerit714

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Rep(i, a, b) for (int i = a; i <= b; ++i)
#define STRING_SIZE 500
#define NULL_CHAR '\0'

int main() {
  puts("Enter a valid left factorable production with only one pipe character");
  printf("Example: A->aB|abCD\n>>> ");
  char s[STRING_SIZE];
  scanf("%[^\n]", s);

  // Point to the current char
  int firstIndexAfterArrow = 3;
  char startingChar = s[0];
  char firstCharAfterArrow = s[firstIndexAfterArrow];
  int len = strlen(s);

  // And find the index of pipe from 3rd char
  char pipe = '|';
  int indexOfPipe;
  Rep(i, firstIndexAfterArrow, len - 1) {
    char currentChar = s[i];
    if (currentChar == pipe) {
      indexOfPipe = i;
      break;
    }
  }

  char alphaChar = NULL_CHAR;
  int nextIndexAfterPipe = indexOfPipe + 1;
  char firstCharAfterPipe = s[nextIndexAfterPipe];
  int isLeftFactoringApplicable = (firstCharAfterArrow == firstCharAfterPipe);

  // Check if left factoring is applicable
  if (isLeftFactoringApplicable) {
    alphaChar = firstCharAfterPipe;
  } else {
    printf("The grammar is not applicable for left factoring\n");
    exit(0);
  }

  // Now to extrach beta1String and beta2String
  char beta1String[STRING_SIZE];
  char beta2String[STRING_SIZE];

  int startIndexOfBeta1String = firstIndexAfterArrow + 1;
  int endIndexOfBeta1String = indexOfPipe - 1;

  int startIndexOfBeta2String = nextIndexAfterPipe + 1;
  int endIndexOfBeta2String = len;
  int i = 0;
  Rep(j, startIndexOfBeta1String, endIndexOfBeta1String) {
    char currentCharInSubString = s[j];
    beta1String[i++] = currentCharInSubString;
  }
  beta1String[i] = NULL_CHAR;

  i = 0;
  Rep(j, startIndexOfBeta2String, endIndexOfBeta2String) {
    char currentCharInSubString = s[j];
    beta2String[i++] = currentCharInSubString;
  }
  beta2String[i] = NULL_CHAR;

  puts("Grammar before left factoring is: ");
  puts(s);

  puts("Grammar after left factoring is: ");
  printf("%c->%c(%c')\n", startingChar, firstCharAfterArrow, startingChar);
  printf("(%c')->%s|%s\n",startingChar, beta1String, beta2String);

  return 0;
}