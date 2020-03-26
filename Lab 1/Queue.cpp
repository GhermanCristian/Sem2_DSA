#include "Queue.h"
#include <exception>

using namespace std;

void Queue::copyInformation(const Queue& originalQueue){
	TElem* newArr = new TElem[originalQueue.capacity];
	delete[] this->arr;
	for (int i = 0; i < this->capacity; i++) {
		newArr[i] = originalQueue.arr[i];
	}
	this->arr = newArr;
}

Queue::Queue() {
	head = 0;
	tail = -1;
	capacity = 100;
	arr = new TElem[capacity];
}

void Queue::push(TElem elem) {
	if ((tail + 1) % capacity == (head % capacity) && tail >= head) {
		// the queue is full, we need to double its capacity
		TElem *newArr = new TElem[capacity * 2];
		if (tail < capacity) {
			for (int i = 0; i < capacity; i++) {
				newArr[i] = arr[i];
			}
		}
		else {
			// we have to copy the array from head to tail, which includes the part of the queue from before the head
			int newPosition = 0;
			for (int i = (head % capacity); i < capacity; i++, newPosition++) {
				newArr[newPosition] = arr[i];
			}
			for (int i = 0; i <= (tail % capacity); i++, newPosition++) {
				newArr[newPosition] = arr[i];
			}
			// set the new head/ tail values (because the new position began from 0 <=> head = 0)
			tail -= (head % capacity);
			head = 0;
		}

		delete[] arr;
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
	delete[] arr;
}

Queue::Queue(const Queue& originalQueue) {
	this->tail = originalQueue.tail;
	this->head = originalQueue.head;
	this->capacity = originalQueue.capacity;
	copyInformation(originalQueue);
}

Queue& Queue::operator = (const Queue& originalQueue) {
	if (this != &originalQueue) {
		this->tail = originalQueue.tail;
		this->head = originalQueue.head;
		this->capacity = originalQueue.capacity;
		copyInformation(originalQueue);
	}
	
	return *this;
}

