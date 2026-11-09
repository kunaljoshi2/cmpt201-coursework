#define POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxInputs 1000

struct input {

  int lineNumber;
  int lineValue;
};

struct intermediateInput {
  int lineNumber;
  int doubledValue;
};

struct output {

  int doubledValue;
  int lineNumbers[maxInputs];
  int count;
};

void map(struct input *input, struct intermediateInput *intermediateInput) {

  intermediateInput->doubledValue = (input->lineValue) * 2;
  intermediateInput->lineNumber = input->lineNumber;
}

void groupByKey(struct intermediateInput *input, struct output *output, int *resultCount) {

  for (int i = 0; i < *resultCount; i++) {

    if (output[i].doubledValue == input->doubledValue) {

      output[i].lineNumbers[output[i].count] = input->lineNumber;

      return;
    }
  }

  output[*resultCount].doubledValue = input->doubledValue;
  resultCount = resultCount + 1;
}

void reduce(struct output output) {

  printf("(%d, [", output.doubledValue);

  for (int i = 0; i < output.count; i++) {

    if (i > 0) {

      printf(" , ");
    }

    printf("%d", output.lineNumbers[i]);
  }

  printf(" ])\n");
}

int main() {

  struct intermediateInput intermediate[maxInputs];
  struct input inputs[maxInputs];
  struct output outputs[maxInputs];

  int valuesEntered = 0;
  char buffer[1000];
  int resultCount = 0;

  printf("Enter values (one per line). Type 'end' to finish:\n");

  while (valuesEntered < maxInputs && scanf("%99s", buffer) == 1) {
    if (strcmp(buffer, "end") == 0) {
      break;
    }

    inputs[valuesEntered].lineNumber = valuesEntered + 1;
    inputs[valuesEntered].lineValue = atoi(buffer);
    valuesEntered = valuesEntered + 1;
  }

  for (int i = 0; i < valuesEntered; i++) {
    map(&inputs[i], &intermediate[i]);
  }

  for (int i = 0; i < valuesEntered; i++) {

    groupByKey(&intermediate[i], outputs, &resultCount);
  }

  // reduce part
  for (int i = 0; i < resultCount; i++) {
    reduce(outputs[i]);
  }

  return 0;
}
