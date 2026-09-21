#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char *lineBuffer = NULL;
  size_t bufferSize = 0;
  int done = 0;

  while (done != 1) {

    printf("Enter some text: ");

    if (getline(&lineBuffer, &bufferSize, stdin) == -1L) {

      break;

    }

    else {

      char *inputStr = lineBuffer;
      char *delimitizer = " \n";
      char *token = NULL;
      char *saveptr = NULL;

      while ((token = strtok_r(inputStr, delimitizer, &saveptr))) {

        printf(" %s\n", token);
        inputStr = NULL;
      }
    }
  }

  free(lineBuffer);
}
