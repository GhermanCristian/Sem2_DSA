#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#define _CRTDBG_MAP_ALLOC // used to check for memory leaks
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

bool relation5(TComp r1, TComp r2) {
	return r1 <= r2;
}

int main() {
	testAll();
	testAllExtended();
	
	cout << "Test over" << endl;

	_CrtDumpMemoryLeaks();

	return 0;
}
