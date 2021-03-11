
	// HashTrie.cpp //

	// C++ implementation of a HashTrie class //

/*
	Implements a trie-like data structure using a HashMap
	to store connections to other nodes in the trie rather
	than an array
*/

	// Local Includes //

#include "HashMap.hpp"

	// Library Includes //

#include <sstream>

// HashTrieNode class definition; individual nodes of the HashTrie
class HashTrieNode
{
	// HashMap mapping characters to HashTrieNodes
	HashMap<char,HashTrieNode> next;

	// Number of entries that end at this node
	unsigned int count;

		// Public Methods //

	public:

			// Operator Overloads //
		
		// x++ operator overload
		// Increment count whenever called
		HashTrieNode operator++(int)
		{
			HashTrieNode old(this->count);
			
			(this->count)++;

			return old;
		}

		// x-- operator overload
		// Decrement count whenever called
		HashTrieNode operator--(int)
		{
			HashTrieNode old(this->count);
			
			(this->count)--;

			return old;
		}

			// Constructors //
		
		// Constructor for HashTrieNode
		HashTrieNode(void) : HashTrieNode(0) {}

			// Methods //

		// Gets the size of this object in bytes 
		// Takes no arguments
		// Returns the size of this node in bytes
		size_t byteSize(void)
		{
			// Initialize the counter to 0
			size_t bytes = 0;

			// Size of the reference and objects inside
			bytes += sizeof(HashTrieNode);

			// Size of the HashMap
			bytes += next.byteSize();

			return bytes;
		}

		// Gets the value stored in count
		// Takes no arguments
		// Returns the value stored in count
		int getCount(void)
		{
			return this->count;
		}

		// Private Methods //

	private:

			// Constructors //

		// Constructor with int argument for HashTrieNode
		HashTrieNode(unsigned int init)
		{
			this->count = init;
		}
};
