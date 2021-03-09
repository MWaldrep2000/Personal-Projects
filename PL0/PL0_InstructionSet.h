
	// PL0_InstructionSet.h //

/* 	Header file containing all instructions relating to the PL0 VM
	Note that this is merely a library of define statements and that
	all instructions must be interpreted as I R L M where:
		I = instruction
		R = register
		L = lexicographic level
		M = modifier
	Note that this convention does not apply to mathematical instructions
*/

	// Program Instructions //

// Store literal M at register R //
// Example: LIT 0 0 3
// Stores 3 at register 0
#define LIT 1

// Return to the previous lexicographical level
#define RTN 2

// Load the value at level L and offset M in R
// Example: LOD 0 2 5
// Loads the value at level 2 with offset of 5 on the stack in register 0
#define LOD 3

// Stores the value in R at level L with offset M
// Example: STO 0 2 5
// Stores that variable at level 2 with offset of 5 from register 0
#define STO 4

// Calls a new function with level L and program counter M
// Example: CAL 0 2 6
// Initiates a new activation record and moves base pointer and program counter accordingly
#define CAL 5

// Adjusts stack pointer by M
// Example: INC 0 0 1
// Increments the stack pointer by 1
#define INC 6

// Jumps to instruction M
// Example: JMP 0 0 5
// Sets program counter to 5
#define JMP 7

// Conditional jumps to instruction M depending on if R == 0
// Example: JPC 0 0 5
// Checks if the value at register 0 is 0, and jumps to line 5 if it is
#define JPC 8

// Writes a value to the screen from register R
// Example: SIO 0 0 1
// Writes the value at register 0 to the screen
// Note: M must be 1
#define SIO_W 9

// Reads a value from the user and places it in register R
// Example: SIO 0 0 2
// Reads an input from the user and stores it at register 0
// Note: M must be 2
#define SIO_R 10

// Terminates the program by setting "halt" to true
// Note: M must be 3
#define SIO_H 11

	// Arithmetic Instructions //

/* 	Considering instruction format I R L M, please note that
	R is the result, L is the first operand, and M is the second operand
*/

// R = -R
#define NEG 12

// R = L + M
#define ADD 13

// R = L - M
#define SUB 14

// R = L * M
#define MUL 15

// R = L / M
#define DIV 16

// R = R mod 2
#define ODD 17

// R = L mod M
#define MOD 18

	// Comparison Instructions //

/*
	Note that R will be 0 if the result is false
	This is important for JPC, as a result of zero indicates that we should
	jump to the given program counter; used primarily for conditionals and while loops
*/

// R = (L == M)
#define EQL 19

// R = (L != M)
#define NEQ 20

// R = (L < M)
#define LSS 21

// R = (L <= M)
#define LEQ 22

// R = (L > M)
#define GTR 23

// R = (L >= M)
#define GEQ 24
