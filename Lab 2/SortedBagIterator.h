#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

	private:
		int currentFrequency; // frequency of the current element
		int currentElement; // current element in the list
		Node* currentNode;

		const SortedBag& bag;
		SortedBagIterator(const SortedBag& b);

	public:
		TComp getCurrent();
		bool valid();
		void next();
		void first();
};

