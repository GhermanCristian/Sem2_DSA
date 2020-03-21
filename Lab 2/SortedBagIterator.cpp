#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	first();
}

TComp SortedBagIterator::getCurrent() {
	if (valid()) {
		;
	}
	return NULL_TCOMP;
}

bool SortedBagIterator::valid() {
	return (position < bag.listLength);
}

void SortedBagIterator::next() {
	if (valid() == false) {
		first();
	}
	else {
		position++;
	}
}

void SortedBagIterator::first() {
	position = 0;
}

