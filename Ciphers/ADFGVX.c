
	// ADFGVX.c //

	// Performs an ADFGVX Cipher on any text //

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Encryption Constants //
#define KEY_BLOCK_DIM 6

// General Constants //
#define FAILURE 1
#define SUCCESS 0

// Swaps characters in pointers a and b
// *a = address to character a
// *b = address to character b
void swapChars(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

// Swaps character pointers in pointers a and b
// *a = address to pointer a
// *b = address to pointer b
void swapCharPointers(char **a, char **b)
{
	char *temp = *a;
	*a = *b;
	*b = temp;
}

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
// *plainText = pointer to the string to be encrypted
// **cipherText = address of where to store the cipherText
// *key = string that is the key
// **block = 2D array for the keyblock, assuming letters and numbers
// Returns a 0 if successful, otherwise a 1
int encrypt(char *plainText, char **cipherText, char *key, char **block)
{
	// Variables //
	
	// ADFGVX reference array
	const char ref[KEY_BLOCK_DIM] = {'A', 'D', 'F', 'G', 'V', 'X'};

	// Columnar transposition array and temp variables
	char **trans;

	// cipherLen = the length of the ciphertext
	// cipKeyRatio = ratio between cipher and key lengths
	// col = column index; used for finding ADFGVX indecies
	// i = iterator variable (primarily used in iterating through rows)
	// j = iterator variable (primarily used in iterating through columns)
	// k = iterator variable (primarily used to iterate through cipherText)
	// keyLen = the length of the key
	// row = row index; used for finding ADFGVX indecies
	// textLen = the length of plaintext
	int cipherLen, cipKeyRatio, col, i, j, k, keyLen, row, textLen;

	// Get the length of the key
	keyLen = strlen(key);

	// Get the length of the plaintext
	textLen = strlen(plainText);

	// From textLen, set the length of the cipherText
	cipherLen = textLen * 2;

	// From cipher and keylen, get ratio
	cipKeyRatio = (cipherLen / keyLen) + (cipherLen % keyLen == 0 ? 1 : 2);

	// Checking Validity //
	
	// No need to check text, key, or block, as we know that they are valid from ADFGVX()

	// Encryption //

	// If the key is GERMAN, and the cipherText is length of 12, then the box will look like this
	// G **
	// E **
	// R **
	// M **
	// A **
	// N **

	// The matrix is built from the top downwards, so if we insert two more characters,
	// then they are appended to G and E in this example.

	// Allocate space for the cipher text; the algorithm doubles the size of the text when encrypting
	*cipherText = malloc(sizeof(char) * ((cipherLen) + 1));

	// Check if malloc was successful
	if (*cipherText == NULL)
	{
		fprintf(stderr, "Error: malloc failed in allocating cipherText.\n");
		return FAILURE;
	}

	// Null terminate the cipher text
	// Considering the fact that the encryption doubles the size of the text,
	// we know that cipherLen will properly terminate the text, as it is double
	// the original plaintext length
	(*cipherText)[cipherLen] = '\0';

	// Iterate and encrypt character by character
	for (i = 0; i < textLen; i++)
	{
		// Retrieve the indecies of the character
		if (findIndecies(block, plainText[i], &row, &col))
		{
			free(*cipherText);

			fprintf(stderr, "Error: character '%c' unrecognized by findIndecies().\n", plainText[i]);
			return FAILURE;
		}

		// Using row and column, generate the first two characters of cipher text
		(*cipherText)[2 * i] = ref[row];
		(*cipherText)[2 * i + 1] = ref[col];
	}

	// Allocate space for the columnar transposition array
	trans = malloc(sizeof(char*) * keyLen);

	// Check if trans was properly allocated
	if (trans == NULL)
	{
		free(*cipherText);

		fprintf(stderr, "Error: malloc failed in allocating trans.\n");
		return FAILURE;
	}

	// Allocate each slot of the columnar transposition array
	for (i = 0; i < keyLen; i++)
	{
		trans[i] = malloc(sizeof(char) * cipKeyRatio);

		// If any of the array is NULL, free everything
		if (trans[i] == NULL)
		{
			// Save the failure index
			j = i;
			
			// Decrement so we don't free null pointers
			i--;

			// Free all previously allocated memory
			while (i >= 0)
			{
				free(trans[i--]);
			}

			free(trans);
			free(*cipherText);

			fprintf(stderr, "Error: malloc failed in allocating trans[%d].\n", j);
			return FAILURE;
		}
	}

	// Place the cipherText into the transposition array
	for (i = 0; i < keyLen; i++)
	{
		for (j = 0; j < cipKeyRatio; j++)
		{
			trans[i][j] = ((j * keyLen + i) < (cipherLen)) ? (*cipherText)[j * keyLen + i] : '\0';
		}
	}

	// Sort the columns in ascending key order using bubble sort
	for (i = 0; i < keyLen - 1; i++)
	{
		for (j = 0; j < keyLen - i - 1; j++)
		{
			// If the current letter is greater than the next, swap
			if (key[j] > key[j + 1])
			{
				swapChars(&(key[j]), &(key[j + 1]));
				swapCharPointers(&(trans[j]), &(trans[j + 1]));
			}
		}
	}

	// Refill the cipher text with the transposed text
	for (i = 0, k = 0; i < keyLen; i++)
	{
		for (j = 0; j < cipKeyRatio; j++)
		{
			if (trans[i][j] != '\0')
			{
				(*cipherText)[k++] = trans[i][j];
			}
		}
	}

	// Memory Cleaning //

	// Free everything in trans, then free trans
	for (i = 0; i < keyLen; i++)
	{
		free(trans[i]);
	}

	free(trans);

	printf("%s\n", *cipherText);

	return SUCCESS;
}

// ADFGVX Cipher function; will either call encrypt or decrypt
// *plainText = pointer to the string to be encrypted or decrypted
// **cipherText = pointer to store the cipherText in
// *key = string that is the key
// **block = 2D array for the keyblock, assuming letters and numbers
// enc = 0 to decrypt, one to encrypt
// Returns a 0 if successful, otherwise a 1
int ADFGVX(char *plainText, char **cipherText, char *key, char **block, int enc)
{
	// Variables //

	// Iterators
	int i;

	// Checking Validity //

	// Check if plainText, cipherText, key, or block are NULL
	if (plainText == NULL || cipherText == NULL || key == NULL || block == NULL)
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
		return encrypt(plainText, cipherText, key, block);
	}

	else
	{
		return decrypt(plainText, key, block);
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

	char stuff[] = {'G', 'E', 'R', 'M', 'A', 'N', '\0'};

	char **newBlock = malloc(sizeof(char*) * KEY_BLOCK_DIM);

	char *cipherText = NULL;

	int i, j;

	for (i = 0; i < KEY_BLOCK_DIM; i++)
	{
		newBlock[i] = malloc(sizeof(char) * KEY_BLOCK_DIM);

		for (j = 0; j < KEY_BLOCK_DIM; j++)
		{
			newBlock[i][j] = block[i][j];
		}
	}

	printf("%d\n", ADFGVX("attack", &cipherText, stuff, newBlock, 1));

	for (i = 0; i < KEY_BLOCK_DIM; i++)
	{
		free(newBlock[i]);
	}

	free(newBlock);

	free(cipherText);

	return 0;
}
