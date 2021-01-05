// prerit714

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define Rep(i, a, b) for (int i = a; i <= b; ++i)
#define STRING_SIZE 500

int main() {
  char s[STRING_SIZE];
  puts("Enter a valid left recursive grammar (# is epsilon): ");
  scanf("%[^\n]", s);

  char startingChar = s[0];
  int len = strlen(s);
  Rep(i, 3, len - 1) {

    // point to the current char and start matching from third string char
    char currentChar = s[i];
    if (currentChar == startingChar) {

      // Find the index of Pipe
      int indexOfPipe;
      Rep(j, 3, len - 1) {
        int currentCharInSubString = s[j];
        if (currentCharInSubString == '|') {
          indexOfPipe = j;
          break;
        }
      }

      // Extract the substring from 3 to indexOfPipe
      char alphaString[STRING_SIZE];
      int i = 0;
      Rep(j, 4, indexOfPipe - 1) {
        alphaString[i++] = s[j];
      }
      alphaString[i] = '\0';

      // Extract the substring from indexOfPipe till the last char
      char betaString[STRING_SIZE];
      i = 0;
      Rep(j, indexOfPipe + 1, len - 1) {
        betaString[i++] = s[j];
      }
      betaString[i] = '\0';

      // Print the final string as output
      puts("Grammar after removal of left recursion is: ");
      printf("%c->%s(%c')\n", startingChar, betaString, startingChar);
      printf("(%c')->%s(%c')|#\n", startingChar, alphaString, startingChar);
    }
  }
  return 0;
}