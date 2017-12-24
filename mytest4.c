#include "machine.h"
#include <stdio.h>
#include <assert.h>

int main() {
  print_instruction(0x00000000);
  print_instruction(0x08000232);
  assert(valid_instruction(0x08000232) == BADREG2);
  printf("yay!");
  print_instruction(0x08000251);
  assert(valid_instruction(0x08000251) == BADREG1);
  printf("yay again!");
  return 0;
}
