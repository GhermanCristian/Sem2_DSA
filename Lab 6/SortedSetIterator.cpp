#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m){
	this->first();
}

void SortedSetIterator::first() {
	this->positionInArray = 0;

	// we go to the left as much as we can, in order to find the minimum value
	while (this->positionInArray * 2 + 1 < this->multime.arrayCapacity 
		and this->multime.elements[this->positionInArray * 2 + 1] != NULL_TELEM) {
		this->positionInArray = this->positionInArray * 2 + 1;
	}
}

void SortedSetIterator::next() {
	if (this->valid() == false) {
		throw std::exception("Invalid iterator position");
	}

	// if it has a right-child
	if (this->positionInArray * 2 + 2 < this->multime.arrayCapacity and this->multime.elements[this->positionInArray * 2 + 2] != NULL_TELEM) {
		// the minimum from the right sub-tree (the first element larger than the current one)
		this->positionInArray = this->multime.getPositionOfMinimum(this->positionInArray * 2 + 2);
	}

	// if it doesn't have a right-child, we need to go up the tree:
	//	- if the current node is a left-child => its parent is the next position
	//	- otherwise, we find the first value larger than the current one
	else{
		if (this->positionInArray % 2 == 1) { // left child
			this->positionInArray = this->multime.getParentPosition(this->positionInArray);
		}
		else {
			int auxPosition = this->multime.getParentPosition(this->positionInArray);
			while (auxPosition >= 0 and this->multime.currentRelation(this->multime.elements[auxPosition], this->multime.elements[this->positionInArray]) == true) {
				if (auxPosition == 0) { // it's the 'maximum' element
					this->positionInArray = this->multime.arrayCapacity; // make the position invalid
					return;
					//throw std::exception("Invalid iterator position");
				}
				auxPosition = this->multime.getParentPosition(auxPosition);
			}
			this->positionInArray = auxPosition;
		}
	}
}

TElem SortedSetIterator::getCurrent(){
	if (this->valid()) {
		return this->multime.elements[this->positionInArray];
	}
	throw std::exception("Invalid iterator position");
}

bool SortedSetIterator::valid() const {
	return this->positionInArray >= 0 and this->positionInArray < this->multime.arrayCapacity and this->multime.elements[this->positionInArray] != NULL_TELEM;
}
