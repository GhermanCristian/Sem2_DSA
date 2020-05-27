#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	this->elementCount = 0;
	this->arrayCapacity = INITIAL_CAPACITY;
	this->elements = new TComp[this->arrayCapacity];
	for (int i = 0; i < this->arrayCapacity; i++) {
		this->elements[i] = NULL_TELEM;
	}
}

bool SortedSet::add(TComp elem) {
	int position = 0;

	while (position < this->arrayCapacity) {
		if (this->elements[position] == NULL_TELEM) {
			this->elements[position] = elem;
			this->elementCount++;
			return true;
		}
		
		if (this->elements[position] == elem) {
			return false; // element already exists
		}

		// left child
		if (elem < this->elements[position]/* and position * 2 + 1 < this->arrayCapacity*/) {
			position = position * 2 + 1;
		}
		// right child
		else if (elem > this->elements[position]/* and position * 2 + 2 < this->arrayCapacity*/) {
			position = position * 2 + 2;
		}
	}

	// somewhere around here there should be a resize
	return false; // we've run out of valid positions in the array
}

bool SortedSet::remove(TComp elem) {
	//TODO - Implementation
	return false;
}

bool SortedSet::search(TComp elem) const {
	int position = 0;

	while (position < this->arrayCapacity) {
		// checks if the root is the element we search for
		if (elem == this->elements[position]) {
			return true;
		}

		// left child (keep in mind that it's 0-indexed)
		if (elem < this->elements[position] and position * 2 + 1 < this->arrayCapacity and this->elements[position * 2 + 1] != NULL_TELEM) {
			position = position * 2 + 1;
		}

		// right child (keep in mind that it's 0-indexed)
		else if (elem > this->elements[position] and position * 2 + 2 < this->arrayCapacity and this->elements[position * 2 + 2] != NULL_TELEM) {
			position = position * 2 + 2;
		}

		else {
			return false;
		}
	}
}

int SortedSet::size() const {
	return this->elementCount;
}

bool SortedSet::isEmpty() const {
	return (this->elementCount == 0);
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	delete[] this->elements;
}