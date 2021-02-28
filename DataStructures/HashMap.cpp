
	// HashMap.cpp //

	// C++ implementation of a HashMap class //

	// Includes //

#include <exception>
#include <functional>
#include <iostream>
#include <sstream>

	// Defines //

// Propositional Constants
#define FALSE 0
#define TRUE 1

// Index Constants
#define DIRTY -1
#define CLEAN 0
#define TAKEN 1

// Size Constants
#define MIN_SIZE 2
#define MAX_SIZE UINT_MAX

// Size Checking Macros
#define MIN(a, b) ((a < b) ? a : b) // Return the min of a and b

// InvalidSizeException
class InvalidSizeException : public std::exception
{
	const char *what(void) const throw()
	{
		return "InvalidSizeException in HashMap; HashMap was initialized with an invalid size.";
	}
};

// KeyDuplicateException
class KeyDuplicateException : public std::exception
{
	const char *what(void) const throw()
	{
		return "KeyDuplicateException in HashMap; the specified key already exists in the table.";
	}
};

// KeyNotFoundException
class KeyNotFoundException : public std::exception
{
	const char *what(void) const throw()
	{
		return "KeyNotFoundException in HashMap; the specified key does not exist.";
	}
};

// HashSet class definition mapping input V to output T
template <class K, class V>
class HashMap
{
	// Capacity is the current amount of allocated space
	// Size is the amount of filled space
	unsigned int capacity, size;

	// The arrays for keys and values
	K *keys;
	V *values;

	// An array to keep track of all indecies in use
	int8_t *index;

	private:
		
		// Get the hash index based on ovject
		// key = the object to get the hashcode of
		// Returns the hashcode of key
		// Note: K maps to V, so key (type K) will return the index of object V
		// Note: does NOT implement any kind of collision resistance policy
		unsigned int getHashIndex(K key)
		{
			std::hash<K> keyHash;
			return keyHash(key);
		}

		// Resizes the hashmap
		// expand = boolean on whether to expand or shrink the hashmap
		// Returns nothing
		void resize(bool expand)
		{
			// Allocate new V and index arrays
			K *tempKeys = new K [this->size];
			V *tempValues = new V [this->size];

			// First collect all of the values from the old array
			for (int i = 0, k = 0; i < this->capacity; i++)
			{
				// If the index is taken, it means that there is a valid key-value pair present
				if (this->index[i] == TAKEN)
				{
					tempKeys[k] = this->keys[i];
					tempValues[k++] = this->values[i];
				}
			}

			// Delete the old arrays
			delete[] this->keys;
			delete[] this->values;
			delete[] this->index;

			// Adjust capacity
			this->capacity = expand ? this->capacity * 2 : MIN(this->capacity / 2, MIN_SIZE);

			// Save the current size and reset
			int currSize = this->size;
			this->size = 0;

			// Allocate new arrays of either double or half the capacity depending on the value of expand
			this->keys = new K [this->capacity];
			this->values = new V [this->capacity];
			this->index = new int8_t [this->capacity];

			// Set the values in index
			for (int i = 0; i < this->capacity; i++)
			{
				this->index[i] = CLEAN;
			}

			// Reinsert the values stored in tempArray into the hash table
			for (int i = 0; i < currSize; i++)
			{
				this->put(tempKeys[i], tempValues[i]);				
			}

			// Delete the tempKeys and tempValues
			delete[] tempKeys;
			delete[] tempValues;
		}

	public:
		
		// Constructors //

		// No argument constructor
		HashMap(void) : HashMap(MIN_SIZE) {}

		// Argument constructor with initial size
		// init = Initial size parameter
		HashMap(unsigned int init)
		{	
			// If init is invalid
			if (init < MIN_SIZE)
			{
				throw (InvalidSizeException());
			}
			
			// Initialize all other members
			this->capacity = init;
			this->size = 0;
			this->keys = new K [init];
			this->values = new V [init];
			this->index = new int8_t [init];

			// Tell the HashMap that all indecies are clean
			for (int i = 0; i < this->capacity; i++)
			{
				index[i] = CLEAN;
			}
		}

		// Destructor //
		~HashMap()
		{
			delete[] this->keys;
			delete[] this->values;
			delete[] this->index;
		}

		// Public Methods //

		// Determines the size of the hashmap in bytes
		// Takes no arguments
		// Returns the number of bytes the object requires as a size_t
		size_t byteSize(void)
		{
			// Initial size
			size_t bytes = 0;

			// Size of the reference along with the objects inside
			bytes += sizeof(HashMap);

			// Add in the lengths of all the values in the arrays
			bytes += ((sizeof(K) + sizeof(V) + sizeof(int8_t)) * this->capacity);

			return bytes;
		}

		// Determines if the given key is in the table
		// key = the key to look for
		// Returns true if the key is found, false if otherwise
		bool containsKey(K key)
		{
			// Get the hash index of the key
			unsigned int base = getHashIndex(key);
			
			// Search through the list using quadratic probing
			for (int i = 0; true; i++)
			{

				// Adjusted index
				int adj = (base + (i * i)) % this->capacity;				

				// If the index is clean
				if (this->index[adj] == CLEAN)
				{
					return false;;
				}

				// If the index has the requested key
				else if (this->keys[adj] == key)
				{
					return true;
				}
			}
		}

		// Determines if the given value is in the table
		// value = the value to look for
		// Returns true if the value is found, false if otherwise
		// Note: LINEAR runtime
		bool containsValue(V value)
		{
			// Initiate linear search through the values array
			for (int i = 0; i < this->capacity; i++)
			{
				// If the index is taken and the value is the value we're looking for
				if (this->index[i] == TAKEN && this->value[i] == value)
				{
					return true;
				}

				return false;
			}
		}

		// Return value found from key
		// key = The value that key first maps to
		// Returns the object found from key
		// Throws a KeyNotFoundException if the key does not exist
		V get(K key)
		{
			// Get the hash index of the key
			unsigned int base = getHashIndex(key);
			
			// Search through the list using quadratic probing
			for (int i = 0; true; i++)
			{

				// Adjusted index
				int adj = (base + (i * i)) % this->capacity;				

				// If the index is clean
				if (this->index[adj] == CLEAN)
				{
					throw(KeyNotFoundException());
				}

				// If the index has the requested key
				else if (this->keys[adj] == key)
				{
					return this->values[adj];
				}
			}
		}

		// Fetches the number of key mappings
		// Takes no arguments
		// Returns the number of key mappings
		unsigned int getSize(void)
		{
			return this->size;
		}

		// Insert V using the hash index generated from K
		// key = the key from which to get the index
		// value = the value that key should map to
		// Returns nothing
		// Throws an exception if the key already exists
		// Note: uses quadratic probing as conflict resolution policy
		void put(K key, V value)
		{			
			// Check if the key already exists
			if (this->containsKey(key))
			{
				throw (KeyDuplicateException());
			}

			// Determine if we need to expand or not
			// Quadratic probing requires that the table must be less than half full
			if (this->size >= this->capacity / 2)
			{
				this->resize(true);
			}

			// Base index of K
			unsigned int base = this->getHashIndex(key);

			// Initiate collision resistance policy
			for (int i = 0; true; i++)
			{

				// Adjusted index
				int adj = (base + (i * i)) % this->capacity;				

				// If the index has nothing in it
				if (this->index[adj] != TAKEN)
				{
					this->index[adj] = TAKEN;
					this->keys[adj] = key;
					this->values[adj] = value;
					break;
				}
			}

			this->size++;
		}

		// Removes and returns a value from key
		// key = The key we should search in
		// Returns the object found from key
		// Throws a KeyNotFoundException if the key does not exist
		V remove(K key)
		{
			// Get the hash index of the key
			unsigned int base = getHashIndex(key);
			
			// Search through the list using quadratic probing
			for (int i = 0; true; i++)
			{

				// Adjusted index
				int adj = (base + (i * i)) % this->capacity;				

				// If the index is clean
				if (this->index[adj] == CLEAN)
				{
					throw (KeyNotFoundException());
				}

				// If the index has the requested key
				else if (this->keys[adj] == key)
				{
					// Mark the index as dirty
					this->index[adj] = DIRTY;
					
					// Save the value found at the key
					V ret = this->values[adj];

					// If the array shrinks to below a certain threshold, resize downwards
					if (--(this->size) < (this->capacity / 2))
					{
						resize(false);
					}

					return ret;
				}
			}
		}

		// Convert and return the hashmap as a string
		// Takes no parameters
		// Returns a string containing the values in the string
		std::string toString(void)
		{
			
			// Declare a string stream to hold the values found in the hashmap
			std::stringstream s("");

			// Iterate through the list and append all items to the stringstrea,
			// k will keep track of how many items we've found
			for (int i = 0, k = 0; i < this->capacity; i++)
			{
				// If the current space isn't taken
				if (this->index[i] != TAKEN)
				{
					continue;
				}
				else
				{
					// Start off the string with the first value
					if (k == 0)
					{
						s << "(" << this->keys[i] << ", " << this->values[i] << ")";
					}
					else
					{
						s << ", " << "(" << this->keys[i] << ", " << this->values[i] << ")";
					}

					k++;
				}
			}

			// Conclude the stringstream with a newline
			s << '\n';

			return s.str();
		}
};

int main(void)
{
	HashMap<int,int> hm;

	hm.put(1, 1);

	hm.byteSize();
	
	return 0;
}
