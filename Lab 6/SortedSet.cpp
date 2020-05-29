#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

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

	// the root will be placed on position 0 => the first empty position is 1
	this->firstEmpty = 1;
	this->nextEmpty[this->arrayCapacity - 1] = NONEXISTENT_POSITION;
}

int SortedSet::findPositionOf(TComp elem) const {
	int position = this->rootPosition;

	if (this->rootPosition == NONEXISTENT_POSITION) { // the set is empty
		return NONEXISTENT_POSITION;
	}

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
	Node* auxArray = new Node[2 * this->arrayCapacity + 1];
	int* auxEmpty = new int[2 * this->arrayCapacity + 1];
	for (int i = 0; i < this->arrayCapacity; i++) {
		auxArray[i] = this->elements[i];
	}
	for (int i = this->arrayCapacity; i < 2 * this->arrayCapacity + 1; i++) {
		auxArray[i] = NULL_NODE;
	}
	delete[] this->elements;
	this->elements = auxArray;

	for (int i = 0; i < 2 * this->arrayCapacity + 1; i++) {
		auxEmpty[i] = i + 1;
	}
	auxEmpty[2 * this->arrayCapacity] = NONEXISTENT_POSITION;
	delete[] this->nextEmpty;
	this->nextEmpty = auxEmpty;

	this->arrayCapacity = 2 * this->arrayCapacity + 1;
}

bool SortedSet::isLeftChild(int position) const {
	return (position != NONEXISTENT_POSITION and position != this->rootPosition and this->elements[this->elements[position].parent].left == position);
}

bool SortedSet::isRightChild(int position) const {
	return (position != NONEXISTENT_POSITION and position != this->rootPosition and this->elements[this->elements[position].parent].right == position);
}

int SortedSet::getPositionOfMaximum(int rootPosition) const {
	while (rootPosition < this->arrayCapacity and this->elements[rootPosition].right != NONEXISTENT_POSITION) {
		rootPosition = this->elements[rootPosition].right;
	}

	return rootPosition;
}

int SortedSet::getPositionOfMinimum(int rootPosition) const {
	while (rootPosition < this->arrayCapacity and this->elements[rootPosition].left != NONEXISTENT_POSITION) {
		rootPosition = this->elements[rootPosition].left;
	}

	return rootPosition;
}

void SortedSet::updateNextEmpty(int position){
	this->nextEmpty[position] = this->firstEmpty;
	this->firstEmpty = position;
}

void SortedSet::removeNoSuccessors(int position){
	this->updateNextEmpty(position);
	
	if (this->isLeftChild(position) == true) {
		this->elements[this->elements[position].parent].left = NONEXISTENT_POSITION;
	}
	// we don't just do 'else' here because if this is a root => isLeftChild is false => it would have entered
	// this block, despite not being a right child
	else if (this->isRightChild(position) == true) {
		this->elements[this->elements[position].parent].right = NONEXISTENT_POSITION;
	}

	// if it's a root, it suffices to just delete the node (because in this case it also doesn't have any successors,
	// so there are no links to maintain)
	else {
		this->rootPosition = NONEXISTENT_POSITION;
	}

	this->elements[position] = NULL_NODE;
}

void SortedSet::removeOneSuccessor(int position, bool hasLeftChild){
	this->updateNextEmpty(position);

	if (this->isLeftChild(position) == true) {
		if (hasLeftChild == true) {
			this->elements[this->elements[position].parent].left = this->elements[position].left;
			this->elements[this->elements[position].left].parent = this->elements[position].parent;
		}
		else { // has a right child
			this->elements[this->elements[position].parent].left = this->elements[position].right;
			this->elements[this->elements[position].right].parent = this->elements[position].parent;
		}
	}
	// we don't just do 'else' here because if this is a root => isLeftChild will return false
	// => will enter this block, although it's not a right child)
	else if (this->isRightChild(position) == true) {
		if (hasLeftChild == true) {
			this->elements[this->elements[position].parent].right = this->elements[position].left;
			this->elements[this->elements[position].left].parent = this->elements[position].parent;
		}
		else { // has a right child
			this->elements[this->elements[position].parent].right = this->elements[position].right;
			this->elements[this->elements[position].right].parent = this->elements[position].parent;
		}
	}

	else { // root
		// it has one child, which will become the new root
		int rootCopy = this->rootPosition;
		if (hasLeftChild == true) {
			this->rootPosition = this->elements[rootCopy].left;
			this->elements[this->elements[rootCopy].left].parent = NONEXISTENT_POSITION;
		}
		else {
			this->rootPosition = this->elements[rootCopy].right;
			this->elements[this->elements[rootCopy].right].parent = NONEXISTENT_POSITION;
		}
	}

	this->elements[position] = NULL_NODE;
}

void SortedSet::removeTwoSuccessors(int position){
	// we know that both left/right children exist (because there are 2 successors)
	int positionOfMaximum = this->getPositionOfMaximum(this->elements[position].left);
	this->elements[position] = this->elements[positionOfMaximum];

	this->updateNextEmpty(positionOfMaximum);
	if (this->isLeftChild(positionOfMaximum) == true) {
		this->elements[this->elements[positionOfMaximum].parent].left = NONEXISTENT_POSITION;
	}
	else if (this->isRightChild(positionOfMaximum) == true) {
		this->elements[this->elements[positionOfMaximum].parent].right = NONEXISTENT_POSITION;
	}
	this->elements[positionOfMaximum] = NULL_NODE;
}

void SortedSet::resetEmpty(){
	for (int i = 0; i < this->arrayCapacity; i++) {
		this->nextEmpty[i] = i + 1;
	}
	this->nextEmpty[this->arrayCapacity - 1] = NONEXISTENT_POSITION;
	this->firstEmpty = 1;
}

void SortedSet::independentListsCopy(const SortedSet& originalSet){
	if (this == &originalSet) {
		return;
	}

	if (this->arrayCapacity != originalSet.arrayCapacity) {
		delete[] this->elements;
		delete[] this->nextEmpty;

		this->elements = new Node[originalSet.arrayCapacity];
		this->nextEmpty = new int[originalSet.arrayCapacity];
	}

	for (int i = 0; i < originalSet.arrayCapacity; i++) {
		this->elements[i] = originalSet.elements[i];
		this->nextEmpty[i] = originalSet.nextEmpty[i];
	}
}

bool SortedSet::add(TComp elem) {
	int position = this->rootPosition;
	int parentPosition = NONEXISTENT_POSITION;
	bool isLeftChild = false; // if this is false => right child

	if (this->rootPosition == NONEXISTENT_POSITION) { // the array is empty
		this->resetEmpty();
		this->addNewNode(elem, 0, isLeftChild, NONEXISTENT_POSITION);
		return true;
	}

	while (position < this->arrayCapacity) {
		if (this->elements[position].info == NULL_TELEM) {
			this->addNewNode(elem, position, isLeftChild, parentPosition);
			return true;
		}
		parentPosition = position;

		if (this->elements[position].info == elem) {
			return false; // element already exists in the set
		}

		if (this->relation(elem, this->elements[position].info) == true) {// left child
			position = this->elements[position].left;
			isLeftChild = true;
		}
		else {// right child
			position = this->elements[position].right;
			isLeftChild = false;
		}

		if (position == NONEXISTENT_POSITION) {
			if (this->firstEmpty == NONEXISTENT_POSITION) { // array is full
				position = this->arrayCapacity;
				this->resizeArray();
				this->firstEmpty = position + 1; // = prev capacity + 1 = nextEmpty[ previous capacity ] 
			}
			else {
				position = this->firstEmpty;
				this->firstEmpty = this->nextEmpty[this->firstEmpty];
			}
		}
	}

	return true;
}

bool SortedSet::remove(TComp elem) {
	int position = this->findPositionOf(elem);
	int successorCount = 0;
	bool hasLeftChild = false;

	if (position == NONEXISTENT_POSITION) {
		return false; // element doesn't exist
	}

	if (this->elements[position].left != NONEXISTENT_POSITION) {
		successorCount++;
		hasLeftChild = true;
	}
	if (this->elements[position].right != NONEXISTENT_POSITION) {
		successorCount++;
	}

	if (successorCount == 0) {
		this->removeNoSuccessors(position);
	}
	else if (successorCount == 1) {
		this->removeOneSuccessor(position, hasLeftChild);
	}
	else {
		this->removeTwoSuccessors(position);
	}

	this->elementCount--;
	return true;
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

SortedSet::SortedSet(const SortedSet& originalSet){
	this->elementCount = originalSet.elementCount;
	this->arrayCapacity = originalSet.arrayCapacity;
	this->firstEmpty = originalSet.firstEmpty;
	this->rootPosition = originalSet.rootPosition;
	this->relation = originalSet.relation;
	this->independentListsCopy(originalSet);
}

SortedSet& SortedSet::operator=(const SortedSet& originalSet){
	if (this != &originalSet) {
		this->elementCount = originalSet.elementCount;
		this->arrayCapacity = originalSet.arrayCapacity;
		this->firstEmpty = originalSet.firstEmpty;
		this->rootPosition = originalSet.rootPosition;
		this->relation = originalSet.relation;
		this->independentListsCopy(originalSet);
	}

	return *this;
}

SortedSet::~SortedSet() {
	delete[] this->elements;
	delete[] this->nextEmpty;
}