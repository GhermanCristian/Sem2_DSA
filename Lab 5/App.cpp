#include "ExtendedTest.h"
#include "ShortTest.h"
#include "Map.h"
#include <iostream>

#define _CRTDBG_MAP_ALLOC // used to check for memory leaks
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

int main() {
	testAll();
	testAllExtended();

	_CrtDumpMemoryLeaks();

	cout << endl << "That's all!" << endl;
	system("pause");
	return 0;
}


