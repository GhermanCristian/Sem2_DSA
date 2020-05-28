#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	this->elementCount = 0;
	this->arrayCapacity = INITIAL_CAPACITY;
	this->elements = new TComp[this->arrayCapacity];
	for (int i = 0; i < this->arrayCapacity; i++) {
		this->elements[i] = NULL_TELEM;
	}
	this->currentRelation = r;
}

int SortedSet::findPositionOf(TComp elem) const {
	int position = 0;

	while (position < this->arrayCapacity) {
		// checks if the root is the element we search for
		if (elem == this->elements[position]) {
			return position;
		}

		// left child (keep in mind that it's 0-indexed)
		if (currentRelation(elem, this->elements[position]) == true and position * 2 + 1 < this->arrayCapacity and this->elements[position * 2 + 1] != NULL_TELEM) {
			position = position * 2 + 1;
		}

		// right child (keep in mind that it's 0-indexed)
		else if (currentRelation(elem, this->elements[position]) == false and position * 2 + 2 < this->arrayCapacity and this->elements[position * 2 + 2] != NULL_TELEM) {
			position = position * 2 + 2;
		}

		else {
			return NONEXISTENT_POSITION;
		}
	}

	return NONEXISTENT_POSITION;
}

void SortedSet::resizeArray() {
	TComp* auxArray = new TComp[this->arrayCapacity * 2 + 1];
	for (int i = 0; i < this->arrayCapacity; i++) {
		auxArray[i] = this->elements[i];
	}

	this->arrayCapacity = this->arrayCapacity * 2 + 1;
	delete[] this->elements;
	this->elements = auxArray;
}

void SortedSet::moveSubtree(int sourcePosition, int destPosition){
	// I will assume the positions are valid and moving will not overwrite other parts of the tree
	this->elements[destPosition] = this->elements[sourcePosition];
	this->elements[sourcePosition] = NULL_TELEM;

	if (sourcePosition * 2 + 1 < this->arrayCapacity and this->elements[sourcePosition * 2 + 1] != NULL_TELEM) {
		moveSubtree(sourcePosition * 2 + 1, destPosition * 2 + 1);
	}
	if (sourcePosition * 2 + 2 < this->arrayCapacity and this->elements[sourcePosition * 2 + 2] != NULL_TELEM) {
		moveSubtree(sourcePosition * 2 + 2, destPosition * 2 + 2);
	}
}

int SortedSet::getPositionOfMaximum(int rootPosition) const{
	// the maximum element is determined by going "to the right" as much as possible
	while (rootPosition * 2 + 2 < this->arrayCapacity and this->elements[rootPosition * 2 + 2] != NULL_TELEM) {
		rootPosition = rootPosition * 2 + 2;
	}

	return rootPosition;
}

int SortedSet::getPositionOfMinimum(int rootPosition) const{
	// the minimum element is determined by going "to the left" as much as possible
	while (rootPosition * 2 + 1 < this->arrayCapacity and this->elements[rootPosition * 2 + 1] != NULL_TELEM) {
		rootPosition = rootPosition * 2 + 1;
	}

	return rootPosition;
}

int SortedSet::getParentPosition(int childPosition) const{
	// keep in mind this is 0-indexed
	if (childPosition % 2 == 1) {
		return childPosition / 2;
	}
	return (childPosition - 1) / 2;
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
		if (currentRelation(elem, this->elements[position]) == true/* and position * 2 + 1 < this->arrayCapacity*/) {
			position = position * 2 + 1;
		}
		// right child
		else if (currentRelation(elem, this->elements[position]) == false/* and position * 2 + 2 < this->arrayCapacity*/) {
			position = position * 2 + 2;
		}
	}

	// we've run out of valid positions in the array, so we have to resize
	this->resizeArray();
	this->elements[position] = elem;
	this->elementCount++;

	return true; 
}

bool SortedSet::remove(TComp elem) {
	int position = this->findPositionOf(elem);
	int successorCount = 0;
	int childPosition;

	if (position == NONEXISTENT_POSITION) {
		return false;
	}

	if (position * 2 + 1 < this->arrayCapacity and this->elements[position * 2 + 1] != NULL_TELEM) {
		successorCount++;
		childPosition = position * 2 + 1;
	}
	if (position * 2 + 2 < this->arrayCapacity and this->elements[position * 2 + 2] != NULL_TELEM) {
		successorCount++;
		childPosition = position * 2 + 2; 
		// in the case with 1 successor, only one of these positions will be the child's position (so either left or right)
	}

	if (successorCount == 0) {
		this->elements[position] = NULL_TELEM;
	}
	else if (successorCount == 1) {
		this->moveSubtree(childPosition, position);
	}
	else {
		// we move the maximum element in this subtree to the current position
		// because it's the max elem, it can have at most 1 successor (one smaller than it => left subtree)
		int maximumPosition = this->getPositionOfMaximum(position);
		this->elements[position] = maximumPosition;
		this->elements[maximumPosition] = NULL_TELEM;

		// if it has a left subtree, we move it in the position which previously belonged to the maximum
		if (maximumPosition * 2 + 1 < this->arrayCapacity and this->elements[maximumPosition * 2 + 1] != NULL_TELEM) {
			this->moveSubtree(maximumPosition * 2 + 1, maximumPosition);
		}
	}

	this->elementCount--;
	return true;
}

bool SortedSet::search(TComp elem) const {
	return (this->findPositionOf(elem) != NONEXISTENT_POSITION);
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