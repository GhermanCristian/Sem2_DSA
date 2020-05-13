#include "Map.h"
#include "MapIterator.h"

Map::Map() {
	this->hashTable = new Node*[INITIAL_HASH_TABLE_SIZE];

	for (int i = 0; i < INITIAL_HASH_TABLE_SIZE; i++) {
		this->hashTable[i] = NULL;
	}

	this->numberOfPairs = 0;
	this->numberOfPositions = INITIAL_HASH_TABLE_SIZE;
	this->hashFunctionDivisionValue = INITIAL_HASH_TABLE_SIZE;
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
	return originalKey % this->hashFunctionDivisionValue;
}

void Map::addToLinkedList(Node*& linkedListHead, TKey elementKey, TValue elementValue){
	Node* newNode = new Node;
	newNode->keyValuePair = std::make_pair(elementKey, elementValue);
	newNode->nextNode = linkedListHead;
	linkedListHead = newNode;
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

bool Map::checkIfOverloaded(){
	return (double)(this->numberOfPairs / this->numberOfPositions) >= HASH_LOAD_FACTOR;
}

void Map::resizeHashTable(){
	Node** auxiliaryList = new Node* [this->numberOfPositions * MULTIPLYING_FACTOR];
	MapIterator iter(*this);
	int newPairKey;

	for (int i = 0; i < this->numberOfPositions * MULTIPLYING_FACTOR; i++) {
		auxiliaryList[i] = NULL;
	}

	this->hashFunctionDivisionValue *= MULTIPLYING_FACTOR; // this will change the hash function
	while (iter.valid()) {
		TElem currentPair = iter.getCurrent();
		newPairKey = this->hashFunction(currentPair.first);
		this->addToLinkedList(auxiliaryList[newPairKey], currentPair.first, currentPair.second);
		iter.next();
	}

	Node* temporaryNode;
	for (int i = 0; i < this->numberOfPositions; i++) {
		while (this->hashTable[i] != NULL) {
			temporaryNode = this->hashTable[i]->nextNode;
			delete this->hashTable[i];
			this->hashTable[i] = temporaryNode;
		}
	}
	delete[] this->hashTable;
	this->numberOfPositions *= MULTIPLYING_FACTOR;
	this->hashTable = auxiliaryList;
}

TValue Map::add(TKey c, TValue v){
	int positionInHashTable = this->hashFunction(c);
	TValue previousValue = NULL_TVALUE;

	if (this->hashTable[positionInHashTable] == NULL) {
		this->addToLinkedList(this->hashTable[positionInHashTable], c, v);
		this->numberOfPairs++;
	}
	else {
		Node* positionInLinkedList = this->searchInLinkedList(positionInHashTable, c);
		if (positionInLinkedList == NULL) {
			this->addToLinkedList(this->hashTable[positionInHashTable], c, v);
			this->numberOfPairs++;
		}
		else {
			previousValue = positionInLinkedList->keyValuePair.second;
			positionInLinkedList->keyValuePair = std::make_pair(c, v); // update
		}
	}

	if (checkIfOverloaded() == true) {
		this->resizeHashTable();
	}

	return previousValue;
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
		this->numberOfPairs--;
		return previousValue;
	}

	Node* positionBeforeKey = this->getNodeBeforeKey(positionInHashTable, c);
	if (positionBeforeKey == NULL) {
		return NULL_TVALUE;
	}

	TValue previousValue = positionBeforeKey->nextNode->keyValuePair.second;
	this->removeFromLinkedList(positionBeforeKey);
	this->numberOfPairs--;
	return previousValue;
}

int Map::size() const {
	return this->numberOfPairs;
}

bool Map::isEmpty() const{
	return this->numberOfPairs == 0;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}



