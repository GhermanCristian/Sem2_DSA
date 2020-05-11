#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;

MapIterator::MapIterator(const Map& d) : map(d){
	this->first();
}

void MapIterator::first() {
	for (int i = 0; i < map.numberOfPositions; i++) {
		if (map.hashTable[i] != NULL) {
			this->positionInHashTable = i;
			break;
		}
	}

	this->positionInLinkedList = map.hashTable[this->positionInHashTable];
}

void MapIterator::next() {
	if (!valid()) {
		throw std::exception("Invalid position");
	}

	if (this->positionInLinkedList->nextNode != NULL) {
		this->positionInLinkedList = this->positionInLinkedList->nextNode;
	}
	else {
		this->positionInHashTable++;
		while (this->positionInHashTable < map.numberOfPositions and map.hashTable[this->positionInHashTable] == NULL) {
			this->positionInHashTable++;
		}

		if (this->positionInHashTable == map.numberOfPositions) {
			this->positionInLinkedList = NULL; // the iterator becomes invalid
		}
		else {
			this->positionInLinkedList = map.hashTable[this->positionInHashTable];
		}
	}
}

TElem MapIterator::getCurrent(){
	if (!valid()) {
		throw std::exception("Invalid position");
	}
	return this->positionInLinkedList->keyValuePair;
}

bool MapIterator::valid() const {
	return this->positionInHashTable < map.numberOfPositions and this->positionInLinkedList != NULL;
}



