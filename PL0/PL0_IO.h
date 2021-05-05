
	// PL0_IO.h //

/*
	This header file contains all file IO operations necessary for the PL0 compiler.

	Possible Inputs:
		-a list of VM instructions
			-should be fed into the code array in VirtualHardware.h
		-a list of symbols
			-should be fed into the parser and converted into VM instructions
		-PL0 code
			-should be fed into the tokenizer and converted into symbols

	Possible Outputs:
		-the virtual machine execution trace
		-the generated assembly code
		-the list of symbols
*/

	// Library Includes //

#include "PL0_VirtualHardware.h"

#include <stdio.h>

	// File Code Constants //

// PL0 code input; .PL0 extension
#define PL0_CODE_INPUT 0

// Symbol list input; .PL0_SYM extension
#define SYMBOL_LIST_INPUT 1

// VM instruction Input; .PL0_VM extension
#define VM_INSTRUCTION_INPUT 2

	// Output File Index Constants //

#define EXECUTION_TRACE 0
#define ASSEMBLY_CODE 1
#define SYMBOL_LIST 2

	// Instruction Parameter Constants /

#define OPCODE 0
#define REGISTER 1
#define LEXI 2
#define MODIFIER 3

	// Input Handling //

// Converts VM text into VM code
// *input = the input file; extension .PL0_VM
	// guaranteed to not be NULL
// Returns nothing; panics on an error
	// NOTE: only used for .PL0_VM files; the input logic is VERY different
	// if the input files is a list of symbols or PL0 code
void readVM(FILE *input)
{
	// Input integer
	int in;

	// Iterator for for-loop
	int i;

	// Iterate through each integer in the file and save to code
	for (i = 0; fscanf(input, "%d", &in) != EOF; i++)
	{
		// If i / 4 exceeds the maximum code length
		if ((i / 4) >= MAX_CODE_LENGTH)
		{
			fclose(input);
			//panic(IO_ERROR, EXCEEDS_CODE_LENGTH);
		}
		
		// Each instruction has four parameters;
		// i % 4 lets us access each element of the array,
		// and i / 4 lets us increment after 4 integers
		switch (i % 4)
		{
			// Read opcode O
			case OPCODE:
				// Check if we can convert in to opcode
				if (!convertToOpcode(&in, &(code.code[i / 4].O)))
				{
					fclose(input);
					//panic(CODE_ERROR, INVALID_OPCODE);
				}
			break;

			// Read register R
			case REGISTER:
				code.code[i / 4].R = in;			
			break;

			// Read lexi L
			case LEXI:
				code.code[i / 4].L = in;
			break;

			// Read modifier M
			case MODIFIER:
				code.code[i / 4].M = in;
			
			// With no break statement, fall through to default
			// and increment size in code
			default:
				code.size++;
		}
	}
}

// The first step in reading a file; determine what it is and then delegate to another function
// *input = the input file; valid extension: .PL0, .PL0_SYM, .PL0_VM
	// guaranteed to not be NULL
// fileCode = tells the function how to interpret the file
	// mainly for convenience, the function could read the extension
// Returns nothing; will panic if a failure is encountered
void readFile(FILE *input, int fileCode)
{
	// Make a decision based on the contents of fileCode
	switch (fileCode)
	{
		// PL0 code
		case PL0_CODE_INPUT:

		break;

		// PL0 symbols
		case SYMBOL_LIST_INPUT:

		break;

		// PL0 VM instructions
		case VM_INSTRUCTION_INPUT:
			readVM(input);
		break;

		// In case fileCode is invalid
		// Note: unless there is a problem in the execution of this program,
		// we will NEVER make it here
		default:
			fclose(input);
			//panic(IO_ERROR, INVALID_INPUT_FILE);
	}
}
