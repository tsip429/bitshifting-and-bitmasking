#include "machine.h"
#include <stdio.h>
#include <assert.h>

int main() {
  print_instruction(0xb0000000);
  assert(valid_instruction(0xb0000000) == BADOPCODE);
  print_instruction(0xa8000000);
  printf("assertion was successful!!");
  return 0;
}
