#pragma once
#include <utility>
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
		int hashFunctionDivisionValue;
		Node** hashTable; // this will store the "heads" of the linked lists

		int hashFunction(TKey originalKey) const;
		void addToLinkedList(Node*& linkedListHead, TKey elementKey, TValue elementValue);
		Node* searchInLinkedList(int positionInHashTable, TKey searchedKey) const;
		Node* getNodeBeforeKey(int positionInHashTable, TKey searchedKey) const;
		void removeLinkedListHead(int positionInHashTable);
		void removeFromLinkedList(Node* positionBeforeKey);
		bool checkIfOverloaded();
		void resizeHashTable();
		void deleteLinkedList(Node*& linkedListHead);
		void deleteHashTable(Node**& hashTable, int numberOfPositions);
		void independentHashTableCopy(const Map& originalMap);

	public:
		Map();
		TValue add(TKey c, TValue v);
		TValue search(TKey c) const;
		TValue remove(TKey c);
		int size() const;
		bool isEmpty() const;
		MapIterator iterator() const;
		Map& operator = (const Map& originalMap);
		Map(const Map& originalMap);
		~Map();
};



