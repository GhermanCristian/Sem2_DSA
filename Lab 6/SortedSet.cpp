#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	this->arrayCapacity = INITIAL_CAPACITY;
	this->elements = new Node[this->arrayCapacity];
	this->nextEmpty = new int[this->arrayCapacity];
	for (int i = 0; i < this->arrayCapacity; i++) {
		this->elements[i] = NULL_NODE;
		this->nextEmpty[i] = i + 1;
	}
	this->elementCount = 0;
	this->relation = r;
	this->rootPosition = 0;

	// the root will be placed on position 0 => the first empty position is 1 = nextEmpty[0]
	this->firstEmpty = 0;
	this->nextEmpty[this->arrayCapacity - 1] = NONEXISTENT_POSITION;
}

int SortedSet::findPositionOf(TComp elem) const {
	int position = this->rootPosition;
	while (position < this->arrayCapacity and this->elements[position].info != NULL_TELEM) {
		if (this->elements[position].info == elem) {
			return position;
		}

		// if it has a left child
		if (this->relation(elem, this->elements[position].info) == true and this->elements[position].left != NONEXISTENT_POSITION) {
			position = this->elements[position].left;
		}

		// if it has a right child
		else if (this->relation(elem, this->elements[position].info) == false and this->elements[position].right != NONEXISTENT_POSITION) {
			position = this->elements[position].right;
		}

		else {
			return NONEXISTENT_POSITION;
		}
	}

	return NONEXISTENT_POSITION;
}

void SortedSet::addNewNode(TComp elem, int position, bool isLeftChild, int parentPosition){
	this->elements[position].info = elem;
	this->elements[position].left = NONEXISTENT_POSITION;
	this->elements[position].right = NONEXISTENT_POSITION;
	this->elements[position].parent = parentPosition;
	this->elementCount++;

	if (parentPosition == NONEXISTENT_POSITION) { // it is a root
		this->rootPosition = position;
	}
	else { // update the left/right of the parent
		if (isLeftChild == true) {
			this->elements[parentPosition].left = position;
		}
		else { // it is a right child
			this->elements[parentPosition].right = position;
		}
	}
}

void SortedSet::resizeArray(){
	;
}

bool SortedSet::add(TComp elem) {
	int position = this->rootPosition;
	int parentPosition = NONEXISTENT_POSITION;
	int temporaryPosition;
	bool isLeftChild = false; // if this is false => right child

	while (position < this->arrayCapacity) {
		if (this->elements[position].info == NULL_TELEM) {
			this->addNewNode(elem, position, isLeftChild, parentPosition);
			return true;
		}

		if (this->elements[position].info == elem) {
			return false; // element already exists in the set
		}

		temporaryPosition = position;
		if (this->relation(elem, this->elements[position].info) == true) {// left child
			position = this->elements[position].left;
			isLeftChild = true;
		}
		else {// right child
			position = this->elements[position].right;
			isLeftChild = false;
		}

		if (position == NONEXISTENT_POSITION) {
			if (this->firstEmpty == NONEXISTENT_POSITION) {
				; // need to resize
			}
			position = this->nextEmpty[this->firstEmpty];
			this->firstEmpty = this->nextEmpty[this->firstEmpty];
			// the value for this element will be set in the next iteration of the while loop
			// (which would've changed the parentPosition, although it's still that previous parent)
			parentPosition = temporaryPosition;
		}
		else {
			parentPosition = position;
		}
	}

	// we've run out of valid positions in the array, so we have to resize
	this->resizeArray();
	this->addNewNode(elem, position, isLeftChild, parentPosition);

	return true;
}

bool SortedSet::remove(TComp elem) {
	//TODO - Implementation
	return false;
}

bool SortedSet::search(TComp elem) const {
	return this->findPositionOf(elem) != NONEXISTENT_POSITION;
}

int SortedSet::size() const {
	return this->elementCount;
}

bool SortedSet::isEmpty() const {
	return this->elementCount == 0;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	//TODO - Implementation
}