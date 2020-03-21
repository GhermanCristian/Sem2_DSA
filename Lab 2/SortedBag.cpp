#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

SortedBag::SortedBag(Relation r) {
	head = nullptr;
	tail = nullptr;
	currentRelation = r;
	listLength = 0; // this may not be required, I might not need the list length when checking if the list is empty
	nrOfElements = 0;
}

void SortedBag::insertBeforeNode(Node* rightNode, TComp info){
	Node* newNode = new Node; // de allocated in the destructor
	newNode->info = info;
	newNode->nrOfOccurences = 1;
	newNode->nextNode = rightNode;

	if (rightNode == head) {
		rightNode->prevNode = newNode;
		newNode->prevNode = nullptr;
		head = newNode;
		return;
	}
	
	if (rightNode == nullptr) {
		newNode->prevNode = tail; // because we can't do rightNode->prevNode
		tail->nextNode = newNode;
		tail = newNode;
		return;
	}

	newNode->prevNode = rightNode->prevNode;
	rightNode->prevNode->nextNode = newNode;
	rightNode->prevNode = newNode;
}

Node* SortedBag::getNodeWithInfo(TComp info) const {
	Node* listIterator = new Node;
	listIterator = head;

	for (; listIterator != nullptr; listIterator = listIterator->nextNode) {
		if (listIterator->info == info) {
			return listIterator;
		}
	}

	return nullptr;
}

Node* SortedBag::getNodeAfterInfo(TComp info) const {
	Node* listIterator = new Node;
	listIterator = head;

	for (; listIterator != nullptr; listIterator = listIterator->nextNode) {
		if (currentRelation(listIterator->info, info) == false) {
			return listIterator;
		}
	}

	return nullptr;
}

void SortedBag::add(TComp e) {
	nrOfElements++;
	if (listLength == 0) {
		Node* newNode = new Node; //de allocated in the destructor
		newNode->info = e;
		newNode->nrOfOccurences = 1;
		newNode->nextNode = nullptr;
		newNode->prevNode = nullptr;
		head = tail = newNode;
		
		listLength++;
		return;
	}

	Node* positionOfElement;
	positionOfElement = getNodeWithInfo(e);

	if (positionOfElement != nullptr) {
		positionOfElement->nrOfOccurences++;
	}
	else {
		positionOfElement = getNodeAfterInfo(e);
		insertBeforeNode(positionOfElement, e);
		listLength++;
	}
}

bool SortedBag::remove(TComp e) {
	if (listLength == 0) {
		return false;
	}

	if (listLength == 1) {
		if (head->info == e && head->nrOfOccurences > 0) {
			nrOfElements--;
			head->nrOfOccurences--;
			if (head->nrOfOccurences == 0) {
				listLength--;
			}

			delete head;
			head = tail = nullptr;
			return true;
		}
		return false;
	}

	Node* elementPosition = getNodeWithInfo(e);
	if (elementPosition == nullptr) {
		return false;
	}
	if (elementPosition->nrOfOccurences <= 0) {
		return false;
	}

	Node* nextNode = elementPosition->nextNode;
	Node* prevNode = elementPosition->prevNode;
	if (nextNode == nullptr) { // last element
		prevNode->nextNode = nullptr;
		tail = prevNode;
	}

	else if (prevNode == nullptr) { // first element
		nextNode->prevNode = nullptr;
		head = nextNode;
	}
	
	else {
		prevNode->nextNode = nextNode;
		nextNode->prevNode = prevNode;
	}

	nrOfElements--;
	elementPosition->nrOfOccurences--;
	if (elementPosition->nrOfOccurences == 0) {
		listLength--;
	}

	delete elementPosition;
	return true;
}

bool SortedBag::search(TComp elem) const {
	return (getNodeWithInfo(elem) != nullptr);
}

int SortedBag::nrOccurrences(TComp elem) const {
	Node* positionOfElement;
	positionOfElement = getNodeWithInfo(elem);
	if (positionOfElement != nullptr) {
		return positionOfElement->nrOfOccurences;
	}
	return 0;
}

int SortedBag::size() const {
	return nrOfElements;
}

bool SortedBag::isEmpty() const {
	return nrOfElements == 0;
}

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

SortedBag::~SortedBag() {
	Node* temporaryNode;
	while (head != nullptr) {
		temporaryNode = head->nextNode;
		delete head;
		head = temporaryNode;
	}
}
