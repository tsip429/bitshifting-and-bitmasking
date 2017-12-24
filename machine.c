#include "machine.h"
#include<stdio.h>
/* Tsipora Stone, 114110213, 0305, tstone97, */

char *opcodes[] = {"halt", "add", "sub", "mul", "div", "mod",
		   "and", "or", "neg", "not", "eql", "neq", "lt",
		   "le", "gt", "ge", "li", "lw", "sw", "move",
		   "branch", "syscall"};
	 
/* takes in the Word instruction and gets the bits at certain positions and 
   assigns them to variables */
int decode_instruction (Word instruction, unsigned short
			*const opcode, unsigned int *const imm_or_addr,
			unsigned short *const reg1,
			unsigned short *const reg2) {
  int rval = 0;
  if (opcode != NULL && imm_or_addr != NULL && reg1 != NULL
      && reg2 != NULL) {
    rval = 1; /* valid parameters */
    /* anding with 0x1f gets the last 5 bits of instruction and assigns
       it to reg2 */
    *reg2 = instruction & 0x1f;
    /* shifts number over to the right by 5 to get the next 5 rightmost
       bits */
    instruction >>= 5;
    /* anding with 0x1f gets the next 5 bits of instruction and assigns
       it to reg1 */
    *reg1 = instruction & 0x1f;
    instruction >>= 5;
    /* anding with 0x1fff to get the next 17 bits of instruction and
       assigns is to imm_or_addr */
    *imm_or_addr = instruction & 0x1ffff;
    /* shifts to right 17 to get the last 5 bits of instruction */
    instruction >>= 17;
    *opcode = instruction;
  }
  return rval;
}

/* prints the word based on certain criteria depending on the word's opcode
   value */
void print_instruction(Word instruction) {
  unsigned short opc = 0;
  unsigned int addr = 0;
  unsigned short reg_one = 0;
  unsigned short reg_two = 0;
  if (valid_instruction(instruction) == VALID) {
    /* calling decode_instruction to get the values of opc, addr, reg_one
       and reg_two */
    decode_instruction (instruction, &opc, &addr, &reg_one, &reg_two);
    /* prints the string that corresponds to that opcode in the string 
       array */
    printf("%s", opcodes[opc]);
    /* in all these cases the first register is a requirement */
    if (opc >= 1 && opc <= 19) {
      printf(" R""%02d", reg_one);
    }
    /* in all these cases the second register is a requirement */
    if (opc == 1 || opc == 2 || opc == 3 || opc == 4 || opc == 5 || opc == 6
	|| opc == 7 || opc == 10 || opc == 11 || opc == 12 || opc == 13
	|| opc == 14 || opc == 15 || opc == 19) {
      printf(" R""%02d", reg_two);
    }
    /* if the operand uses an immediate operand (just in the case of 
       opcode = 16) */
    if (opc == 16) {
      /* checking if the variable is 4 digits or less - prints in 4 places
	 if it is, else just prints in however many places it needs */
      if (addr < 10000) {
	printf(" %04d", addr);
      }
      else { 
	printf(" %d", addr);
      }
    }
    /* if the opcode requires a memory address print address in 4 decimal
       places */ 
    if (opc == 17 || opc == 18 || opc == 20) {
      printf(" %04d", addr);
    }
    printf("\n");
  }
}

/* takes in a program as an array and assigns to memory array in the 
   correct location depending on the start_addr */
int load_program(Word memory[], unsigned int start_addr, 
		 const Word program[], unsigned int program_size) {
  int i;
  int rval = 0;
  unsigned short opc = 0; 
  unsigned int i_or_a = 0; 
  unsigned short r1 = 0; 
  unsigned short r2 = 0; 
  if ((memory != NULL && program != NULL) && (program_size <= 2048)
      && (start_addr % 4 == 0) && (start_addr/4 + program_size <= 2048)) {
    /* looping through program array */
    for (i = 0; i < program_size; i++) {
      if (valid_instruction(program[i]) == VALID) {
	rval = 1;
	/* assigns the value at that location in program to correct 
	   location in memory by dividing by 4 to start at the 
	   leftmost positon and adding i with each new word from 
	   program array */ 
	memory[i + (start_addr/4)] = program[i];
	/*decodes for each word in the array */
	decode_instruction(memory[i + (start_addr/4)], &opc,
			   &i_or_a, &r1, &r2);
	/* if opcode requires a memory address */
	if (opc == 17 || opc == 18 || opc == 20) {
	  /* and the word with 0's in the address spot of the word to set
	     the address to 0 and then or with the start_addr + old memory 
	     address to update memory address of the word */ 
	  memory[i + (start_addr/4)] &= 0xf80003ff;
	  i_or_a += start_addr;
	  memory[i + (start_addr/4)] |= (i_or_a << 10);
	}
      }
    }
  }
  return rval;
}
    

/* checks if the 4 components of a word are valid based on the zapdragon 
   machine restrictions */
Instr_status valid_instruction(Word word) {
  unsigned short opc = 0;
  unsigned int i_or_a = 0;
  unsigned short reg_one = 0;
  unsigned short reg_two = 0;
  if (decode_instruction (word, &opc, &i_or_a, &reg_one, &reg_two) == 1) {
    if (opc >= 22) {
      return BADOPCODE;
    }
    /* the cases where the first register is required */
    if (opc >= 1 || opc <= 19) { 
      if (reg_one >= 18) {
	return BADREG1;
      }
    }
    /* the cases where the second register is required */
    if ((opc >= 1 && opc <= 7) || (opc >= 10 && opc <= 15) || opc == 19) { 
      if (reg_two >= 18) {
	return BADREG2;
      }
    }
    /* the cases where a memory address is required */
    if (opc == 17 || opc == 18 || opc == 20) {
      /* if the memory address is too big or not divisible by 4 it is 
	 invalid */
      if (i_or_a >= 8192 || i_or_a % 4 != 0) {
	return BADADDR;
      }
    }
  }
  return VALID;
}
