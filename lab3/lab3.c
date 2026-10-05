#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  int done = 0;
  char *arr[5] = {NULL};

  int count = 0;

  while (done != 1) {

    printf("Enter input: ");
    char *lineBuffer = NULL;
    size_t bufferSize = 0;

    ssize_t input = getline(&lineBuffer, &bufferSize, stdin);

    if (input == -1) {

      break;
    }

    else {

      free(arr[count % 5]);
      arr[count % 5] = lineBuffer;
      count = count + 1;

      if (strcmp(lineBuffer, "print\n") == 0) {
        int start;
        int numLines;

        if (count < 5) {

          start = 0;
          numLines = count;

        } else {
          start = count % 5;
          numLines = 5;
        }

        for (int i = 0; i < numLines; i++) {
          printf("%s", arr[(start + i) % 5]);
        }
      }
    }
  }
}
