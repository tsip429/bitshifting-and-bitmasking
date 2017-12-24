#include "machine.h"
#include <stdio.h>
#include <assert.h>

#define PROGRAM_SIZE 1
int main() {
  Word memory[NUM_WORDS] = {0};
  Word program[PROGRAM_SIZE] = {0xb0000000};
  assert(load_program(memory, 0, program, PROGRAM_SIZE) == 0);
  printf("yay");
  return 0;
}
