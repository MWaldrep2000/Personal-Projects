
	// HashMap.cpp //

	// C++ implementation of a HashMap class //

	// Includes //

#include <cstdlib>
#include <functional>
#include <iostream>
#include <sstream>
#include <type_traits>

	// Defines //

// Propositional COnstants
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

// HashSet class definition mapping input V to output T
template <class K, class V>
class HashMap
{
	// Capacity is the current amount of allocated space
	// Size is the amount of filled space
	int capacity, size;

	// The arrays for keys and values
	K *keys;
	V *values;

	// An array to keep track of all indecies in use
	int *index;

	// Boolean to determine if the values of primitive or pointers
	bool isPrimitive;

	private:

		// Wraps a primitive type up into a pointer
		// object = the object to be boxed
		// Returns either nothing if autoboxing is unnecessary or the pointer if successful
		// WARNING: USES MALLOC AND NOT NEW
		V *autoBox(V object)
		{
			// Check if the object in question is a pointer
			if (!this->isPrimitive)
			{
				return NULL;
			}

			return std::malloc(sizeof(object));
		}
		
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
				// If the index isn't TAKEN, ignore it
				if (this->index[i] != TAKEN)
				{
					continue;
				}

				else
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
			this->index = new int [this->capacity];

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
		HashMap(int init)
		{
			// First, determine if the value type is primitive
			this->isPrimitive = std::is_fundamental<V>::value;
			
			// Initialize all other members
			this->capacity = init;
			this->size = 0;
			this->keys = new K [init];
			this->values = new V [init];
			this->index = new int [init];

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

		// Return value found from key
		// key = The value that key first maps to
		// Returns the object found from key
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
					return NULL;
				}

				// If the index has the requested key
				else if (this->keys[adj] == key)
				{
					return this->values[adj];
				}
			}
		}

		// Insert V using the hash index generated from K
		// key = the key from which to get the index
		// value = the value that key should map to
		// Returns nothing
		// Note: uses quadratic probing as conflict resolution policy
		void put(K key, V value)
		{			
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
					return NULL;
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
	std::cout << sizeof(8) << '\n';
	
	HashMap<int,int> hm;

	return 0;
}
