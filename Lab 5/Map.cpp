#include "Map.h"
#include "MapIterator.h"

Map::Map() {
	this->hashTable = new Node*[INITIAL_HASH_TABLE_SIZE];

	for (int i = 0; i < INITIAL_HASH_TABLE_SIZE; i++) {
		this->hashTable[i] = NULL;
	}

	this->numberOfPairs = 0;
	this->numberOfPositions = INITIAL_HASH_TABLE_SIZE;
	this->hashConstant = INITIAL_HASH_TABLE_SIZE;
}

Map::~Map() {
	this->deleteHashTable(this->hashTable, this->numberOfPositions);
}

int Map::hashFunction(TKey originalKey) const {
	if (originalKey < 0) {
		originalKey = -originalKey;
	}
	return originalKey % this->hashConstant;
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
	Node* currentNode = this->hashTable[positionInHashTable];

	while (currentNode->nextNode != NULL) {
		if (currentNode->nextNode->keyValuePair.first == searchedKey) {
			return currentNode;
		}
		currentNode = currentNode->nextNode;
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
	Node** auxiliaryHashTable = new Node* [this->numberOfPositions * MULTIPLYING_FACTOR];
	Node* currentNode;
	int newPairKey;

	this->hashConstant *= MULTIPLYING_FACTOR; // this will change the hash function
	for (int i = 0; i < this->numberOfPositions * MULTIPLYING_FACTOR; i++) {
		auxiliaryHashTable[i] = NULL;
	}
	for (int i = 0; i < this->numberOfPositions; i++) {
		currentNode = this->hashTable[i];
		while (currentNode != NULL) {
			newPairKey = this->hashFunction(currentNode->keyValuePair.first);
			this->addToLinkedList(auxiliaryHashTable[newPairKey], currentNode->keyValuePair.first, currentNode->keyValuePair.second);
			currentNode = currentNode->nextNode;
		}
	}

	deleteHashTable(this->hashTable, this->numberOfPositions);
	this->numberOfPositions *= MULTIPLYING_FACTOR;
	this->hashTable = auxiliaryHashTable;
}

void Map::deleteLinkedList(Node*& linkedListHead){
	Node* temporaryNode;
	while (linkedListHead != NULL) {
		temporaryNode = linkedListHead->nextNode;
		delete linkedListHead;
		linkedListHead = temporaryNode;
	}
}

void Map::deleteHashTable(Node**& hashTable, int numberOfPositions){
	// in the copy constructor, this part is called before actually allocating memory for the hash table
	// so it crashed when it got here;
	// we now ensure against that -> if the list isn't even allocated, we don't need to delete it
	if (hashTable == NULL) {
		return;
	}

	for (int i = 0; i < numberOfPositions; i++) {
		this->deleteLinkedList(hashTable[i]);
	}
	delete[] hashTable;
}

void Map::copyHashTable(const Map& originalMap){
	Node* currentNode;

	// this should be done with the previous number of positions (hence why in the assignment operator it is called
	// before changing it) - because if the number differs we might access unavailable memory
	this->deleteHashTable(this->hashTable, this->numberOfPositions);
	this->hashTable = new Node * [originalMap.numberOfPositions];
	for (int i = 0; i < originalMap.numberOfPositions; i++) {
		this->hashTable[i] = NULL;
		currentNode = originalMap.hashTable[i];
		while (currentNode != NULL) {
			this->addToLinkedList(this->hashTable[i], currentNode->keyValuePair.first, currentNode->keyValuePair.second);
			currentNode = currentNode->nextNode;
		}
	}
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

Map& Map::operator=(const Map& originalMap){
	if (this != &originalMap) {
		// I have changed the order here because this will need to destroy a list which was allocated
		// (as opposed to the copy constr, which destroys an un-allocated list -> I prevented that by
		// checking if the list is NULL (<=> it wasn't allocated yet)
		// In this case, however, there already is a list, whose number of elements might differ from the new one
		// in which case the deletion algorithm will try to access unavailable memory (because the number of
		// positions has been updated - most probably increased - prior to the deletion
		this->copyHashTable(originalMap);
		this->numberOfPairs = originalMap.numberOfPairs;
		this->numberOfPositions = originalMap.numberOfPositions;
		this->hashConstant = originalMap.hashConstant;
	}

	return *this;
}

Map::Map(const Map& originalMap){
	this->numberOfPairs = originalMap.numberOfPairs;
	this->numberOfPositions = originalMap.numberOfPositions;
	this->hashConstant = originalMap.hashConstant;
	this->copyHashTable(originalMap);
}

std::vector<TKey> Map::keySet() const {
	std::vector<TKey> mapKeys;

	for (int i = 0; i < this->numberOfPositions; i++) {
		Node* currentNode = this->hashTable[i];
		while (currentNode != NULL) {
			mapKeys.push_back(currentNode->keyValuePair.first);
			currentNode = currentNode->nextNode;
		}
	}

	return mapKeys;
}



