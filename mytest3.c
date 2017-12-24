#include "machine.h"
#include <stdio.h>
#include <assert.h>

int main() {
  print_instruction(0xa0800000);
  assert(valid_instruction(0xa0800000) == BADADDR);
  printf("yay!");
  return 0;
}
