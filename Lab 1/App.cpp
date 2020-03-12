#include "Queue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <iostream>

using namespace std;

int main() {

	Queue q1;
	Queue q2;
	q2 = q1;

	testAll();
	testAllExtended();

	cout << "Test end" << endl;
	
	return 0;
}