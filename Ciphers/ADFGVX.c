
	// ADFGVX.c //

	// Performs an ADFGVX Cipher on any text //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Encryption Constants //
#define KEY_BLOCK_DIM 6
#define MIN_KEY_LEN 6

#define A 0
#define D 1
#define F 2
#define G 3
#define V 4
#define X 5

// General Constants //
#define FAILURE 1
#define SUCCESS 0

// Finds indecies in key block for character c
// **block = key block, a 2D char array containing all alphanumeric characters
// c = the character to search for
// *row = a pointer for row
// *col = a pointer for col
// Returns 0 if successful, otherwise 1
int findIndecies(char **block, char c, int *row, int *col)
{
	// Variables //

	// Iterators
	int i, j;

	// Validity Checking //

	// We know that block is valid
	// Check row and col
	if (row == NULL || col == NULL)
	{
		return FAILURE;
	}

	// Function Mechanics //

	// Iterate through all characters in **block
	// Check for character c
	for (i = 0; i < KEY_BLOCK_DIM; i++)
	{
		for (j = 0; j < KEY_BLOCK_DIM; j++)
		{	
			// If we find c, update row and col and return
			if (block[i][j] == c)
			{
				*row = i;
				*col = j;
				return SUCCESS;
			}
		}
	}

	return FAILURE;
}

// ADFGVX Cipher decryption function
// *text = pointer to the string to be decrypted
// *key = string that is the key
// **block = 2D array for the keyblock, assuming letters and numbers
// Returns a 0 if successful, otherwise a 1
int decrypt(char *text, char *key, char **block)
{
	return SUCCESS;
}

// ADFGVX Cipher encryption function
// *text = pointer to the string to be encrypted
// *key = string that is the key
// **block = 2D array for the keyblock, assuming letters and numbers
// Returns a 0 if successful, otherwise a 1
int encrypt(char *text, char *key, char **block)
{
	// Variables //
	
	// ADFGVX reference array
	const char ref[KEY_BLOCK_DIM] = {'A', 'D', 'F', 'G', 'V', 'X'};

	// Column and row variables for block
	int col = 0, row = 0;

	// Iterators
	int i;

	// Length of text
	int len = strlen(text);

	// Checking Validity //
	
	// No need to check text, key, or block, as we know that they are valid from ADFGVX()

	// Encryption //

	// Allocate space for the cipher text; the algorithm doubles the size of the text when encrypting
	char *cipherText = malloc(sizeof(char) * ((len * 2) + 1));

	// Check if malloc was successful
	if (cipherText == NULL)
	{
		return FAILURE;
	}

	// Iterate and encrypt character by character
	for (i = 0; i < len; i++)
	{
		// 1. Retrieve the indecies of the character
		if (findIndecies(block, text[i], &row, &col))
		{
			return FAILURE;
		}

		// 2. Using row and column, generate the first two characters of cipher text
		cipherText[2 * i] = ref[row];
		cipherText[2 * i + 1] = ref[col];
	}

	// Null terminate the cipher text
	cipherText[len * 2] = '\0';

	// TODO:
	// Implement key and columnar transposition

	return SUCCESS;
}

// ADFGVX Cipher function; will either call encrypt or decrypt
// *text = pointer to the string to be encrypted or decrypted
// *key = string that is the key
// **block = 2D array for the keyblock, assuming letters and numbers
// enc = 0 to decrypt, one to encrypt
// Returns a 0 if successful, otherwise a 1
int ADFGVX(char *text, char *key, char **block, int enc)
{
	// Variables //

	// Iterators
	int i;

	// Checking Validity //

	// Check if text, key, or block are NULL
	if (text == NULL || key == NULL || block == NULL)
	{
		return FAILURE;
	}
	
	// Check if any of the subarrays of block are NULL
	for (i = 0; i < KEY_BLOCK_DIM; i++)
	{
		// If (for some reason), block[i] is NULL, then return FAILURE
		if (block[i] == NULL)
		{
			return FAILURE;
		}
	}

	// Encryption or Decryption //

	// If encrypt is 1, then encrypt, otherwise decrypt
	if (enc)
	{
		return encrypt(text, key, block);
	}

	else
	{
		return decrypt(text, key, block);
	}

}

// Main //
int main(void)
{
	const char block[KEY_BLOCK_DIM][KEY_BLOCK_DIM] = {
						{'p', 'h', '0', 'q', 'g', '6'},
						{'4', 'm', 'e', 'a', '1', 'y'},
						{'l', '2', 'n', 'o', 'f', 'd'},
						{'x', 'k', 'r', '3', 'c', 'v'},
						{'s', '5', 'z', 'w', '7', 'b'},
						{'j', '9', 'u', 't', 'i', '8'}
					};

	char **newBlock = malloc(sizeof(char*) * KEY_BLOCK_DIM);

	int i, j;

	for (i = 0; i < KEY_BLOCK_DIM; i++)
	{
		newBlock[i] = malloc(sizeof(char) * KEY_BLOCK_DIM);

		for (j = 0; j < KEY_BLOCK_DIM; j++)
		{
			newBlock[i][j] = block[i][j];
		}
	}

	printf("%d\n", ADFGVX("attack", "GERMAN", newBlock, 1));

	return 0;
}