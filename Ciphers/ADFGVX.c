
	// ADFGVX.c //

	// Performs an ADFGVX Cipher on any text //

#include <stdio.h>
#include <string.h>

// Encryption Constants //
#define KEY_BLOCK_DIM 6

#define A 0
#define D 1
#define F 2
#define G 3
#define V 4
#define X 5

// General Constants //
#define FAILURE 1
#define SUCCESS 0

// ADFGVX Cipher decryption function
// *text = pointer to the string to be decrypted
// *key = string that is the key
// **block = 2D array for the keyblock, assuming letters and numbers
// Returns a 0 if successful, otherwise a 1
int decrypt(char *text, char *key, char** block)
{
	return SUCCESS;
}

// ADFGVX Cipher encryption function
// *text = pointer to the string to be encrypted
// *key = string that is the key
// **block = 2D array for the keyblock, assuming letters and numbers
// Returns a 0 if successful, otherwise a 1
int encrypt(char *text, char *key, char** block)
{
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

	// Check if key is of a valid length //
	if (strlen(key) != 6)
	{
		return FAILURE;
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
	return 0;
}