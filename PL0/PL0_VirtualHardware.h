
	// PL0_VirtualHardware.h //

/*
	Header file containing the implementation of the PL0 virtual hardware
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

/*
	This is the hardware simulation of the virtual machine.

	Components are as follows:
		pc = program counter; the current instruction the VM is on
		sp = stack pointer; the current value we are pointing to on the stack
		bp = base pointer; the base of the current activation record
		ir = current instruction we are executing

		code = the array of instructions; obtained either from IO or parsing
		R = the registers of this system
		stack = the stack of this system
*/

	// Program Counter
	int pc = 0;

	// Stack and base pointers
	int sp = 0, bp = 1;

	// Instruction Register
	Instruction ir;

	// Instruction array struct
	// code = the array of instructions
	// size = the number of instructions in the array
	typedef struct CodeStruct
	{
		Instruction code[MAX_CODE_LENGTH];
		int size = 0;
	} Code;

	// Declaration of the struct
	Code code;

	// Registers
	int R[MAX_REGISTERS] = {0};

	// Stack struct
	// stack = the simulated stack of this hardware
	// aridx = the indecies at which new activation records start
	typedef struct StackStruct
	{
		int stack[MAX_STACK_HEIGHT] = {0};
		int aridx[MAX_LEXI_LEVELS] = {0};
	} Stack;

	// Declaration of the struct
	Stack stack;
