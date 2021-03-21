
	// PL0_Compiler.c //

/*
	This is the main driver for the compiler; the program entry point.

	Simply contains a main function that processes command line arguments
	and routes their contents to the correct method.

	Main will accept the dedicated PL0 extensions AS WELL as text files,
	HOWEVER, text files will be interpreted as PL0 code by default.

	Special flags will be used to denote if assembly instructions
	or a lexeme list are being passed as a text file.

	Simply typing in ./a.out (or whatever the output executable is) will bring
	up instructions on how to utilize this program as well as possible flags.

	Possible flags in command line execution are:

		-a [filename]
			==> output the generated assembly code to filename.txt
			==> default is PL0_assembly.txt if no filename is specified

		-A
			==> output the generated assembly code to the terminal
		
		-i ".extension" or -interpret ".extension"
			==> used if reading plaintext files as VM code or a lexeme list
			==> .extension can be .PL0, .PL0_SYM, or .PL0_VM
			==> example: ./a.out VM_code.txt -i .PL0_VM

		-l [filename]
			==> output the lexeme information to filename.txt
			==> default is PL0_lexemes.txt if no filename is specified

		-L
			==> output the lexeme information to the terminal

		-v [filename]
			==> output the virtual machine execution trace to filename.txt
			==> default is PL0_execution.txt if no filename is specified

		-V
			==> output the virtual machine execution trace to the terminal

		Arguments can be specified in any order, but they must all be passed
		with their own '-' meaning that if one wishes to pass '-a' and '-l'
		as arguments, then they cannot be passed as '-al'
*/

// Main function
// Program entry point here
int main(int argc, char **argv)
{
	// Iterator for argument list
	int i;
	
	// Check if argc is 1
	// Equivalent of if there was a help flag
	if (argc == 1)
	{
		// display help info
		// will likely be located in a file
	}
}
