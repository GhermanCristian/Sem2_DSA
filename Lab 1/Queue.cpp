#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;

Queue::Queue() {
	head = 0;
	tail = -1;
	capacity = 10000;
	arr = new TElem[capacity];
}

void Queue::push(TElem elem) {
	if ((tail + 1) % capacity == head && tail != -1) {
		// the queue is full, we need to double its capacity
		TElem *newArr = new TElem[capacity * 2];
		for (int i = 0; i < capacity; i++) {
			newArr[i] = arr[i];
		}
		delete arr;
		arr = newArr;
		capacity *= 2;
	}
	tail++;
	arr[tail % capacity] = elem;
}

TElem Queue::top() const {
	if (isEmpty()) {
		throw exception("empty queue");
	}
	return arr[head % capacity];
}

TElem Queue::pop() {
	if (isEmpty()) {
		throw exception("empty queue");
	}
	TElem topElement = top();
	head++;
	return topElement;
}

bool Queue::isEmpty() const {
	return (head == tail + 1);
}

Queue::~Queue() {
	delete arr;
}

