#include "Queue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <iostream>

#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

using namespace std;

int main() {
	testAll();
	testAllExtended();

	cout << "Test end" << endl;
	if (_CrtDumpMemoryLeaks()) {
		cout << "leaks\n";
	}
	
	return 0;
}