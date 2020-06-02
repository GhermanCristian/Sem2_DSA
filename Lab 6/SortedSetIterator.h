#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator{
	friend class SortedSet;

	private:
		const SortedSet& multime;
		int position; // position in the set's array

		SortedSetIterator(const SortedSet& m);
		/*
			Constructor
			Complexity:
				- BC/AC/WC: theta(n) (n = current array capacity)
			Input:
				- The set we iterate through
			Output:
				- The object is built
				- The iterator is set on the first position
		*/

	public:
		void first();
		/*
			Sets the iterator on the first position, or makes it invalid if the set is empty
			Complexity:
				- BC: theta(1), if the minimum element is at the root
				- AC: theta(n)
				- WC: theta(n) (n = current array capacity)
			Input:
				- None
		*/

		void next();
		/*
			Sets the iterator on the next available position, or makes it invalid if there are no available positions left
			Throws exception if the current position is invalid
			Complexity:
				- BC: theta(1), if the node has a right child or is a left child
				- AC: theta(n)
				- WC: theta(n) (n = current array capacity), otherwise
			Input:
				- None
		*/

		TElem getCurrent();
		/*
			Returns the current element in the set, if the position is valid
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- None
			Output:
				- Throws exception if the current position is invalid
		*/

		bool valid() const;
		/*
			Checks if the current position is valid
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- None
			Output:
				- Returns true, if the position is valid
				- Returns false, otherwise
		*/
};