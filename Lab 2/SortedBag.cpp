#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>

SortedBag::SortedBag(Relation r) {
	head = nullptr;
	tail = nullptr;
	currentRelation = r;
	listLength = 0;
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
	for (Node* listIterator = head; listIterator != nullptr; listIterator = listIterator->nextNode) {
		// the search ends when we get past the point where the element should have been 
		// or when we find the exact element that we need
		if (currentRelation(listIterator->info, info) == false or listIterator->info == info) {
			return listIterator;
		}
	}

	return nullptr;
}

bool SortedBag::foundExactElement(Node* possiblePosition, TComp info) const {
	return (possiblePosition != nullptr and possiblePosition->info == info);
}

void SortedBag::independentCopyOfList(const SortedBag& originalSortedBag){
	for (Node* listIterator = originalSortedBag.head; listIterator != nullptr; listIterator = listIterator->nextNode) {
		Node* newNode = new Node;
		newNode->info = listIterator->info;
		newNode->nrOfOccurences = listIterator->nrOfOccurences;
		newNode->nextNode = newNode->prevNode = nullptr;

		if (listIterator == originalSortedBag.head) {
			this->head = this->tail = newNode;
		}
		else {
			this->tail->nextNode = newNode;
			newNode->prevNode = this->tail;
			newNode->nextNode = nullptr; // to be more clear, although it's pointless
			this->tail = newNode;
		}
	}
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

	if (foundExactElement(positionOfElement, e) == true) {
		positionOfElement->nrOfOccurences++;
	}
	else {
		insertBeforeNode(positionOfElement, e);
		listLength++;
	}
}

bool SortedBag::removeFromListWithOneElement(TComp e) {
	if (head->info == e && head->nrOfOccurences > 0) {
		nrOfElements--;
		head->nrOfOccurences--;
		if (head->nrOfOccurences == 0) {
			listLength--;
			delete head;
			head = tail = nullptr;
		}
		return true;
	}
	return false;
}

void SortedBag::deleteNode(Node* elementPosition){
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

	delete elementPosition;
	listLength--;
}

bool SortedBag::remove(TComp e, Node* elementPosition) {
	if (listLength == 0) {
		return false;
	}

	if (listLength == 1) {
		return removeFromListWithOneElement(e);
	}

	// 2 or more elements
	if (elementPosition == nullptr) {
		elementPosition = getNodeWithInfo(e);
	}
	
	if (foundExactElement(elementPosition, e) == false) {
		return false; // element does not exist
	}
	if (elementPosition->nrOfOccurences <= 0) {
		return false; // safety check; normally if an element has no occurences it is removed from the list
	}

	nrOfElements--;
	elementPosition->nrOfOccurences--;

	if (elementPosition->nrOfOccurences == 0) {
		deleteNode(elementPosition);
	}

	return true;
}

int SortedBag::removeOccurences(int nrOccurences, TComp currentElement){
	if (nrOccurences < 0) {
		throw std::exception("Invalid nr of occurences");
	}

	if (listLength == 0 or nrOccurences == 0) {
		return 0;
	}

	int nrRemoved;
	Node* currentPosition = getNodeWithInfo(currentElement);
	for (nrRemoved = 0; remove(currentElement, currentPosition) == true and nrRemoved < nrOccurences; nrRemoved++);
	return nrRemoved;
}

bool SortedBag::search(TComp elem) const {
	return (foundExactElement(getNodeWithInfo(elem), elem));
}

int SortedBag::nrOccurrences(TComp elem) const {
	Node* positionOfElement;
	positionOfElement = getNodeWithInfo(elem);
	if (foundExactElement(positionOfElement, elem) == true) {
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

SortedBag::SortedBag(const SortedBag& originalSortedBag) {
	this->currentRelation = originalSortedBag.currentRelation;
	this->listLength = originalSortedBag.listLength;
	this->nrOfElements = originalSortedBag.nrOfElements;
	this->head = this->tail = nullptr;
	independentCopyOfList(originalSortedBag);
}

SortedBag& SortedBag::operator = (const SortedBag& originalSortedBag){
	if (this != &originalSortedBag) {
		this->currentRelation = originalSortedBag.currentRelation;
		this->listLength = originalSortedBag.listLength;
		this->nrOfElements = originalSortedBag.nrOfElements;
		this->head = this->tail = nullptr;
		independentCopyOfList(originalSortedBag);
	}
	return (*this);
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
