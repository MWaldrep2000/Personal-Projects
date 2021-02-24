
	// HashMap.cpp //

	// C++ implementation of a HashMap class //

	// Includes //
#include <functional>

using namespace std;

	// Defines //

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

	// The array which output V will be stored in
	V *array;

	// An array to keep track of all indecies in use
	int *index;

	private:

		// Get the hash index based on ovject
		// key = the object to get the hashcode of
		// Returns the hashcode of key
		// Note: K maps to V, so key (type K) will return the index of object V
		// Note: does NOT implement any kind of collision resistance policy
		unsigned int getHashIndex(K key)
		{
			return std::hash<K>(key) % capacity;
		}

		// Resizes the hashmap
		// expand = boolean on whether to expand or shrink the hashmap
		// Returns nothing
		void resize(bool expand)
		{
			// Allocate new V and index arrays
			V *tempArray = new V [this->size];

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
					tempArray[k++] = this->array[i];
				}
			}

			// Delete the old arrays
			delete[] this->array;
			delete[] this->index;

			// Allocate new arrays of either double or half the capacity depending on the value of expand
			this->array = new V [expand ? this->capacity * 2 : MIN(this->capacity / 2, MIN_SIZE)];
			this->index = new bool [expand ? this->capacity * 2 : MIN(this->capacity / 2, MIN_SIZE)];

			// Set the values in index
			for (int i = 0; i < (expand ? this->capacity * 2 : MIN(this->capacity / 2, MIN_SIZE)); i++)
			{
				this->index[i] = CLEAN;
			}

			// Reinsert the values stored in tempArray into the hash table
			for (int i = 0; i < this->size; i++)
			{
				this->insert(tempArray[i]);
			}

			// Adjust capacity
			this->capacity = expand ? this->capacity * 2 : MIN(this->capacity / 2, MIN_SIZE);

			// Delete the tempArray
			delete[] tempArray;

		}

	public:
		
		// Constructors //

		// No argument constructor
		HashMap(void)
		{
			this.HashSet(MIN_SIZE);
		}

		// Argument constructor with initial size
		// init = Initial size parameter
		HashMap(int init)
		{
			this->capacity = init;
			this->size = 0;
			this->array = new V [init];
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
			delete[] this->array;
			delete[] this->index;
		}

		// Public Methods //

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
				int adj = base + (i * i);				

				// If the index has nothing in it
				if (this->index[adj] != TAKEN)
				{
					this->index[adj] = TAKEN;
					this->array[adj] = value;
				}
			}

			this->size++;
		}
};

int main(void)
{
	HashMap<int,int> hm(2);

	return 0;
}
