#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

class Queue
{
private:
	int head;
	int tail;
	int capacity;
	TElem *arr;

public:
	Queue();
	/*
		Queue constructor
		Complexity:
			- O(1)
		Input:
			- None
		Output:
			- Creates an object of type Queue
		Throws:
			- None
	*/

	void push(TElem e);
	/*
		Pushes an element to the end of the queue
		Complexity:
			- O(n), n = current capacity of the queue
		Input:
			- e = TElem, which will be added to the queue
		Output:
			- None
		Throws:
			- None
	*/

	TElem top() const;
	/*
		Determines the element from the front of the queue
		Complexity:
			- O(1)
		Input:
			- None
		Output:
			- Returns an object of type TElem (the head of the queue)
		Throws:
			- Exception if the queue is empty
	*/

	TElem pop();
	/*
		Determines and removes the element from the front of the queue
		Complexity:
			- O(1)
		Input:
			- None
		Output:
			- Removes the current head of the queue
			- Returns an object of type TElem (the former head of the queue)
		Throws:
			- Exception if the queue is empty	
	*/

	bool isEmpty() const;
	/*
		Checks if the queue is empty
		Complexity:
			- O(1)
		Input:
			- None
		Output:
			- true, if the queue is empty
			- false, otherwise
		Throws:
			- None
	*/

	~Queue();
	/*
		Queue destructor
		Complexity:
			- O(1)
		Input:
			- None
		Output:
			- Destroys the current queue
		Throws:
			- None
	*/
};
