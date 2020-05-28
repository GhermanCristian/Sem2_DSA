#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

#define _CRTDBG_MAP_ALLOC // used to check for memory leaks
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

int main() {
	testAll();
	testAllExtended();

	_CrtDumpMemoryLeaks();

	cout << "Test end" << endl;
	system("pause");
}