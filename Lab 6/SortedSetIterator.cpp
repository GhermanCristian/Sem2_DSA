#include "SortedSetIterator.h"
#include <exception>
#include <iostream>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m){
	this->first();
}

void SortedSetIterator::first() {
	this->position = this->multime.rootPosition;

	if (this->position == NONEXISTENT_POSITION) { // if the set is empty => no sense in having an iterator
		this->position = this->multime.arrayCapacity; // makes the position invalid
		return;
	}

	// the first position is the one of the minimum of the set
	this->position = this->multime.getPositionOfMinimum(this->position);
}

void SortedSetIterator::next() {
	if (this->valid() == false) {
		throw std::exception("Invalid iterator position");
	}

	// it has a right-child
	if (this->multime.elements[this->position].right != NONEXISTENT_POSITION) {
		// the minimum from the right sub-tree (the first element larger than the current one)
		this->position = this->multime.getPositionOfMinimum(this->multime.elements[this->position].right);
	}

	// if it doesn't have a right-child, we need to go up the tree:
	//	- if the current node is a left-child => its parent is the next position
	//	- otherwise, we find the first value larger than the current one
	else {
		if (this->multime.isLeftChild(this->position) == true) {
			this->position = this->multime.elements[this->position].parent;
		}

		else {
			int auxPosition = this->multime.elements[this->position].parent;

			while (auxPosition >= 0 and this->multime.relation(this->multime.elements[auxPosition].info, this->multime.elements[this->position].info) == true) {
				if (auxPosition == 0) { // it's the 'maximum' element
					this->position = this->multime.arrayCapacity; // make the position invalid
					return;
					//throw std::exception("Invalid iterator position");
				}
				auxPosition = this->multime.elements[auxPosition].parent;
			}
			this->position = auxPosition;
		}
	}
}

TElem SortedSetIterator::getCurrent(){
	if (this->valid() == false) {
		throw std::exception("Invalid iterator position");
	}

	return this->multime.elements[this->position].info;
}

bool SortedSetIterator::valid() const {
	return this->position >= 0 and this->position < this->multime.arrayCapacity and this->multime.elements[this->position].info != NULL_TELEM;
}