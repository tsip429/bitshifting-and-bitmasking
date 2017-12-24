#include "machine.h"
#include <stdio.h>
#include <assert.h>

#define PROGRAM_SIZE 2049
int main() {
Word memory[NUM_WORDS]= {0};
Word program[PROGRAM_SIZE]= {0x0800014b, 0x180001ce, 0x2800016c, 0x3800020f,
                               0xa0003000, 0x580001ac, 0x6000020b, 0x6800016f};
 assert(load_program(memory, 21, program, PROGRAM_SIZE) == 0);
 printf("passed!");
 assert(load_program(memory, 20, program, PROGRAM_SIZE) == 0);
 printf("passed again!");
 return 0;
}
