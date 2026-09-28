#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

  int done = 1;
  char *lineBuffer = NULL;
  size_t bufferSize = 0;

  while (done != 0) {

    printf("Enter program to run: ");
    printf("\n> ");

    ssize_t result = getline(&lineBuffer, &bufferSize, stdin);

    if (result == -1L) {

      break;
    }

    else {

      lineBuffer[result - 1] = '\0';

      if (lineBuffer[0] == '\0') {
        continue;
      }

      int parentStatus = 0;
      pid_t pid = fork();

      if (pid == 0) {
        execlp(lineBuffer, lineBuffer, NULL);
        perror("Error");
        exit(EXIT_FAILURE);
      }

      if (pid == -1) {
        perror("Error");
        continue;
      }

      if (pid > 0) {
        int waitPid = waitpid(pid, &parentStatus, 0);

        if (waitPid == -1) {
          perror("Error");
        }
      }
    }
  }
}
