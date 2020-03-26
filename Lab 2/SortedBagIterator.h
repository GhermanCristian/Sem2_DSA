#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

	private:
		int currentFrequency; // frequency of the current element
		int currentElement; // current element in the list
		Node* currentNode; // the node associated with the current element
		const SortedBag& bag;

		SortedBagIterator(const SortedBag& b);
		/*
			Constructor
			Complexity:
				- O(1)
			Input:
				- None
			Output:
				- Creates a new iterator, which is set on the first position of the SortedBag
		*/

	public:
		TComp getCurrent();
		/*
			Determines the current element of the SortedBag
			Complexity:
				- O(1)
			Input:
				- None
			Output:
				- Returns the element from the SortedBag pointed at by the iterator
		*/

		bool valid();
		/*
			Checks if the current position in the SortedBag is valid
			Complexity:
				- O(1)
			Input:
				- None
			Output:
				- Returns true, if the position (hence the validator) is valid
				- False, otherwise
		*/

		void next();
		/*
			Advances to the next element in the SortedBag
			Complexity:
				- O(1)
			Input:
				- None
			Output:
				- The iterator moves on to the next element in the SortedBag
		*/

		void first();
		/*
			Sets the iterator to the first position in the SortedBag
			Complexity:
				- O(1)
			Input:
				- None
			Output:
				- The iterator is set to the first position in the SortedBag
		*/

};

