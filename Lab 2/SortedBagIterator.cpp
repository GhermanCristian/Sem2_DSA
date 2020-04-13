#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	first();
}

TComp SortedBagIterator::getCurrent() {
	if (valid()) {
		return currentNode->info;
	}
	throw exception("Invalid position");
}

bool SortedBagIterator::valid() {
	return (currentNode != nullptr and currentFrequency < currentNode->nrOfOccurences);
}

void SortedBagIterator::next() {
	if (!valid()) {
		throw exception("Invalid position");
	}
	currentFrequency++;
	if (currentFrequency == currentNode->nrOfOccurences) {
		currentFrequency = 0;
		currentNode = currentNode->nextNode;
	}
}

void SortedBagIterator::first() {
	currentFrequency = 0;
	currentNode = bag.head;
}

