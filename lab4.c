#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

int main() {

  void *heap = sbrk(256);

  if (heap == (void *)-1) {
    perror("Error");
    exit(0);

  }

  else {

    struct header *first = (struct header *)heap;
    struct header *second = (struct header *)heap + 128;

    first->size = 128;
    first->next = NULL;
    second->size = 128;
    second->next = first;

    int dataSize = 128 - sizeof(struct header);

    char *firstData = (char *)first + sizeof(struct header);
    char *secondData = (char *)second + sizeof(struct header);

    memset(firstData, 0, dataSize);
    memset(secondData, 1, dataSize);

    printf("first block:       %p\n", &first);
    printf("second block:      %p\n", &second);
    printf("first block size:  %lu\n", first->size);
    printf("first block next:  %p\n", first->next);
    printf("second block size: %lu\n", second->size);
    printf("second block next: %p\n", second->next);

    for (int i = 0; i < dataSize; i++) {
      printf("%d\n", firstData[i]);
    }

    for (int i = 0; i < dataSize; i++) {
      printf("%d\n", secondData[i]);
    }
  }
}
