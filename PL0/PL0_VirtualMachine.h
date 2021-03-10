
	// PL0_VirtualMachine.h //

/*
	Header file containing the implementation of the PL0 virtual machine
*/

#include "PL0_InstructionSet.h"

	// Size Constants //

// Max number of instructions
#define MAX_CODE_LENGTH 256

// Max number of lexicographical levels
#define MAX_LEXI_LEVELS 4

// Max number of registers
#define MAX_REGISTERS 8

// Max size of the stack
#define MAX_STACK_HEIGHT 64

	// Virtual Hardware //

	// Program Counter
	int pc = 0;

	// Stack and base pointers
	int sp = 0, bp = 1;

	// Instruction Register
	Instruction ir;

	// Registers
	int R[MAX_REGISTERS] = {0};

	// Stack
	int stack[MAX_STACK_HEIGHT] = {0};
