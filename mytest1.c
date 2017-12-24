#include "machine.c"
int main() {
  print_instruction(0x400001e0);
  print_instruction(0x480001a0);
  print_instruction(0xa0036000);
  print_instruction(0xa8000000);
  print_instruction(0x00000000);

  return 0;
}
