#include "Map.h"
#include "MapIterator.h"

Map::Map() {
	this->hashTable = new Node*[INITIAL_HASH_TABLE_SIZE];

	for (int i = 0; i < INITIAL_HASH_TABLE_SIZE; i++) {
		this->hashTable[i] = NULL;
	}

	this->numberOfElements = 0;
	this->numberOfPositions = INITIAL_HASH_TABLE_SIZE;
}

Map::~Map() {
	Node* temporaryNode;
	for (int i = 0; i < this->numberOfPositions; i++) {
		while (this->hashTable[i] != NULL) {
			temporaryNode = this->hashTable[i]->nextNode;
			delete this->hashTable[i];
			this->hashTable[i] = temporaryNode;
		}
	}
	delete[] this->hashTable;
}

int Map::hashFunction(TKey originalKey) const {
	if (originalKey < 0) {
		originalKey = -originalKey;
	}
	return originalKey % this->numberOfPositions;
}

void Map::addToLinkedList(int positionInHashTable, TKey elementKey, TValue elementValue){
	Node* newNode = new Node;
	newNode->keyValuePair = std::make_pair(elementKey, elementValue);
	newNode->nextNode = this->hashTable[positionInHashTable];
	this->hashTable[positionInHashTable] = newNode;
}

Node* Map::searchInLinkedList(int positionInHashTable, TKey searchedKey) const {
	Node* currentNode = this->hashTable[positionInHashTable];
	
	while (currentNode != NULL) {
		if (currentNode->keyValuePair.first == searchedKey) {
			return currentNode;
		}
		currentNode = currentNode->nextNode;
	}

	return NULL;
}

Node* Map::getNodeBeforeKey(int positionInHashTable, TKey searchedKey) const {
	Node* currentPosition = this->hashTable[positionInHashTable];

	while (currentPosition->nextNode != NULL) {
		if (currentPosition->nextNode->keyValuePair.first == searchedKey) {
			return currentPosition;
		}
		currentPosition = currentPosition->nextNode;
	}

	return NULL;
}

void Map::removeLinkedListHead(int positionInHashTable){
	Node* nextNodeCopy = this->hashTable[positionInHashTable]->nextNode;
	delete this->hashTable[positionInHashTable];
	this->hashTable[positionInHashTable] = nextNodeCopy;
}

void Map::removeFromLinkedList(Node* positionBeforeKey){
	// next will always be != NULL
	Node* nextNextNodeCopy = positionBeforeKey->nextNode->nextNode;
	delete positionBeforeKey->nextNode;
	positionBeforeKey->nextNode = nextNextNodeCopy;
}

TValue Map::add(TKey c, TValue v){
	int positionInHashTable = this->hashFunction(c);

	if (this->hashTable[positionInHashTable] == NULL) {
		this->addToLinkedList(positionInHashTable, c, v);
		this->numberOfElements++;
	}
	else {
		Node* positionInLinkedList = this->searchInLinkedList(positionInHashTable, c);
		if (positionInLinkedList == NULL) {
			this->addToLinkedList(positionInHashTable, c, v);
			this->numberOfElements++;
		}
		else {
			TValue previousValue = positionInLinkedList->keyValuePair.second;
			positionInLinkedList->keyValuePair = std::make_pair(c, v); // update
			return previousValue;
		}
	}

	return NULL_TVALUE;
}

TValue Map::search(TKey c) const{
	int positionInHashTable = this->hashFunction(c);

	if (this->hashTable[positionInHashTable] == NULL) {
		return NULL_TVALUE;
	}

	Node* positionInLinkedList = this->searchInLinkedList(positionInHashTable, c);
	if (positionInLinkedList == NULL) {
		return NULL_TVALUE;
	}
	return positionInLinkedList->keyValuePair.second;
}

TValue Map::remove(TKey c){
	int positionInHashTable = this->hashFunction(c);

	if (this->hashTable[positionInHashTable] == NULL) {
		return NULL_TVALUE;
	}

	if (this->hashTable[positionInHashTable]->keyValuePair.first == c) {
		TValue previousValue = this->hashTable[positionInHashTable]->keyValuePair.second;
		this->removeLinkedListHead(positionInHashTable);
		this->numberOfElements--;
		return previousValue;
	}

	Node* positionBeforeKey = this->getNodeBeforeKey(positionInHashTable, c);
	if (positionBeforeKey == NULL) {
		return NULL_TVALUE;
	}

	TValue previousValue = positionBeforeKey->keyValuePair.second;
	this->removeFromLinkedList(positionBeforeKey);
	this->numberOfElements--;
	return previousValue;
}

int Map::size() const {
	return this->numberOfElements;
}

bool Map::isEmpty() const{
	return this->numberOfElements == 0;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}



