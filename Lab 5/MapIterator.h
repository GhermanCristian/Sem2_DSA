#pragma once
#include "Map.h"

class MapIterator{
	//DO NOT CHANGE THIS PART
	friend class Map;

	private:
		const Map& map;
		int positionInHashTable;
		Node* positionInLinkedList;

		MapIterator(const Map& m);
		/*
			Constructor
			Complexity:
				- BC: theta(1), when the first available linked list is the first one
				- AC: theta(n) (n = number of positions in the hash table)
				- WC: theta(n), when the first available linked list is the last one
			Input:
				- The Map on which we iterate
			Output:
				- The object is built, the iterator is set on the first available position
		*/

	public:
		void first();
		/*
			Sets the iterator on the first available position
			Complexity:
				- BC: theta(1), when the first available linked list is the first one
				- AC: theta(n) (n = number of positions in the hash table)
				- WC: theta(n), when the first available linked list is the last one
			Input:
				- None
			Output:
				- The positionInHashTable and positionInLinkedList are set accordingly
		*/

		void next();
		/*
			Sets the iterator on the next available position
			Complexity:
				- BC: theta(1), when the next position is in the same linked list or in the one right after
				- AC: theta(n)
				- WC: theta(n), when the next position is in the last linked list
			Input:
				- None
			Output:
				- The positionInHashTable and positionInLinkedList are set accordingly, if possible
				- Throws an exception, otherwise
		*/

		TElem getCurrent();
		/*
			Determines the element currently pointed at by the iterator
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- None
			Output:
				- Returns the element currently pointed at by the iterator, if it is valid
				- Throws an exception, otherwise
		*/

		bool valid() const;
		/*
			Checks if the iterator is valid
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- None
			Output:
				- Returns true if the iterator is valid, false otherwise
		*/
};


