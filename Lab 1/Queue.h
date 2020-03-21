#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

class Queue
{
private:
	int head; // position in the array of the head of the queue
	int tail; // position in the array of the tail of the queue
	int capacity; // current capacity of the queue
	TElem *arr; // the array which will hold the elements of the queue

public:
	Queue();
	/*
		Queue constructor
		Complexity:
			- O(1)
		Input:
			- None
		Output:
			- Creates a new, empty, object of type Queue
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
			- An element is added to the end of the queue
			- The array is resized if the number of elements exceeds its capacity
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

	Queue(const Queue& newQueue);
	/*
		Copy constructor
		Complexity:
			- O(n), n = capacity of newQueue
		Input:
			- newQueue = object of type Queue, whose content will be copied to the current Queue object
		Output:
			- The content of newQueue is copied to the current Queue
		Throws:
			- None
	*/

	Queue& operator = (const Queue& newQueue);
	/*
		Assignment operator
		Complexity:
			- O(n), n = capacity of newQueue
		Input:
			- newQueue = object of type Queue, whose content will be copied to the current Queue object
		Output:
			- A new object of type Queue, with the same properties as newQueue
		Throws:
			- None
	*/
};
