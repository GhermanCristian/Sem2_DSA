#pragma once
#include <utility>
#include <vector>
//DO NOT INCLUDE MAPITERATOR

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TELEM pair<TKey, TValue>(-11111, -11111)
const double HASH_LOAD_FACTOR = 0.7;
const int MULTIPLYING_FACTOR = 2;
const int INITIAL_HASH_TABLE_SIZE = 50;
class MapIterator;

struct Node {
	TElem keyValuePair;
	Node* nextNode = NULL;
};

class Map {
	//DO NOT CHANGE THIS PART
	friend class MapIterator;

	private:
		int numberOfPairs;
		int numberOfPositions;
		int hashConstant; // used in the hash function
		Node** hashTable; // this will store the "heads" of the linked lists

		int hashFunction(TKey originalKey) const;
		/*
			The function which associates a key with a position in the hash table
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The key we want to process
			Output:
				- Returns the position in the hash table
		*/

		void addToLinkedList(Node*& linkedListHead, TKey elementKey, TValue elementValue);
		/*
			Adds a new pair to the beginning of a linked list
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The linked list we add to
				- The key and value of the new pair
			Output:
				- A new pair is created and added to the beginning of the linked list
		*/

		Node* searchInLinkedList(int positionInHashTable, TKey searchedKey) const;
		/*
			Searches for a key in a linked list
			Complexity:
				- BC: theta(1), when the element is the head of the linked list
				- AC: theta(alpha)
				- WC: theta(n), when all the elements of the hash table are in this linked list
			Input:
				- The position in the hash table, from which we get the linked list
				- The key we search for
			Output:
				- Returns the Node* which contains the given key (if the key is found)
				- Returns NULL otherwise
		*/

		Node* getNodeBeforeKey(int positionInHashTable, TKey searchedKey) const;
		/*
			Searches for a key in a linked list
			Complexity:
				- BC: theta(1), when the element is the head of the linked list
				- AC: theta(alpha)
				- WC: theta(n), when all the elements of the hash table are in this linked list
			Input:
				- The position in the hash table, from which we get the linked list
				- The key we search for
			Output:
				- Returns the Node* BEFORE the one which contains the given key (if the key is found)
				- Returns NULL otherwise
		*/

		void removeLinkedListHead(int positionInHashTable);
		/*
			Removes the head of the linked list at a given position in the hash table
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The position of the linked list in the hash table
			Output:
				- The head of the linked list is removed, and its memory is deallocated
				- The next value becomes the new head
		*/

		void removeFromLinkedList(Node* positionBeforeKey);
		/*
			Removes a node from a linked list
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The node before the one we want to delete (because it is a singly-linked list)
			Output:
				- The correct node is deleted; the link between the nodes is maintained
		*/

		bool checkIfOverloaded();
		/*
			Checks if the hash table has become overloaded
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The number of pairs, the number of hash table position, and the load factor are all known
			Output:
				- Returns true, if the hash table is overloaded, and false, otherwise
		*/

		void resizeHashTable();
		/*
			Resizes and rehashes the hash table
			Complexity:
				- BC/AC/WC: theta(n)
			Input:
				- None
			Output:
				- The hashTable dynamic array is enlarged
				- The hash function is modified
				- The elements are readded to the hashTable, using the new hash function
		*/

		void deleteLinkedList(Node*& linkedListHead);
		/*
			Deletes a linked list
			Complexity:
				- BC: theta(alpha)
				- AC: theta(alpha)
				- WC: theta(n), if all the elements in the hash table are in this list
			Input:
				- The head of the linked list
			Output:
				- The list is deleted
		*/

		void deleteHashTable(Node**& hashTable, int numberOfPositions);
		/*
			Deletes an entire hash table
			Complexity:
				- BC/AC/WC: theta(n)
			Input:
				- The hash table that we want to delete
				- The number of positions (linked lists) in the hash table
			Output:
				- The hash table is deleted
		*/

		void copyHashTable(const Map& originalMap);
		/*
			Copies the hash table from another Map (used in the copy constructor and the overloaded assignment op)
			Complexity:
				- BC/AC/WC: theta(n)
			Input:
				- The map we copy from
			Output:
				- The current hash table contains the content of the one from originalMap
		*/

	public:
		Map();
		/*
			Constructor
			Complexity:
				- BC/AC/WC: theta(n)
			Input:
				- The initial number of positions in the hash table
			Output:
				- The object is created and initialized with NULL
		*/

		TValue add(TKey c, TValue v);
		/*
			Adds a new key-value pair to the Map
			Complexity:
				- BC: theta(1) amortized, when the key is about to be added to an empty linked list
				(amortized because we might have to resize/ rehash the list)
				- AC: theta(alpha) amortized
				- WC: theta(n)
			Input:
				- The key and value of the new pair
			Output:
				- The pair is added, if the key didn't exist already
				- The value associated to the key is updated, otherwise
				- The hash table is resized/ rehashed if it becomes overloaded
		*/

		TValue search(TKey c) const;
		/*
			Searches for a key in the Map
			Complexity:
				- BC: theta(1), if it is the first element in its respective linked list
				- AC: theta(alpha)
				- WC: theta(n), when all the elements of the Map are in the same linked list
			Input:
				- The key we search for
			Output:
				- Returns the value associated to the key, if the key is found
				- Returns NULL_TVALUE, otherwise
		*/

		TValue remove(TKey c);
		/*
			Removes the pair with a given key from the Map
			Complexity:
				- BC: theta(1), if it is the first element in its respective linked list
				- AC: theta(alpha)
				- WC: theta(n), when all the elements of the Map are in the same linked list
			Input:
				- The key of the pair we want to remove
			Output:
				- The pair is removed from the Map, and its value is returned (if the key was found)
				- Returns NULL_TVALUE, otherwise
		*/

		int size() const;
		/*
			Returns the number of pairs in the Map
			Complexity:
				- BC/AC/WC: theta(1)
		*/

		bool isEmpty() const;
		/*
			Checks if the Map is empty
			Complexity:
				- BC/AC/WC: theta(1)
		*/

		MapIterator iterator() const;
		/*
			Returns an iterator for the current Map
			Complexity:
				- BC: theta(1), when the first available position of the iterator is the first position in the hash table
				- AC: theta(n) (n = number of positions in the hash table)
				- WC: theta(n), when the first available position of the iterator is the last one			
			Input:
				- None
		*/

		Map& operator = (const Map& originalMap);
		/*
			Overloaded assignment operator
			Complexity:
				- BC/AC/WC: theta(n)
			Input:
				- The map we copy from
			Output:
				- The content of the originalMap is copied to the current one
		*/

		Map(const Map& originalMap);
		/*
			Copy constructor
			Complexity:
				- BC/AC/WC: theta(n)
			Input:
				- The map we copy from
			Output:
				- A new object with the content of the originalMap is built
		*/

		std::vector <TKey> keySet() const;
		/*
			Returns a the set of all keys from the map
			Complexity:
				- BC/AC/WC: theta(n + m) (n = number of elements in the map, m = number of pos in the hash table)
			Input:
				- The map we iterate through
			Output:
				- The set of all keys in the map
		*/

		~Map();
		/*
			Destructor
			Complexity:
				- BC/AC/WC: theta(n)
			Input:
				- None
			Output:
				- Deallocates the memory of the hash table (and deletes it)
		*/
};



