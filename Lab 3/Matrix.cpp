#include "Matrix.h"
#include <exception>
using namespace std;

void Matrix::insertElement(int line, int column, TElem value){
	if (value == 0) {
		removeElement(line, column);
		return;
	}
	
	int position = getPositionLargerThan(value);
	if (position == -1) {
		; // we add the element to the end of the list
	}
	else {
		;
	}

	this->nrElements++;
}

void Matrix::removeElement(int line, int column){
	this->nrElements--;
}

int Matrix::getPositionLargerThan(TElem value){
	int currentPosition;
	for (currentPosition = this->head; currentPosition != -1 and value > elements[currentPosition].getValue(); currentPosition = nextPosition[currentPosition]);

	return currentPosition; // if -1 => the element should be appended to the list (there is no "larger")
}

Matrix::Matrix(int nrLines, int nrCols) {
	this->numberOfLines = nrLines;
	this->numberOfColumns = nrCols;

	// initialising the SLLA
	this->capacity = INITIAL_CAPACITY;
	this->elements = new MatrixElement[this->capacity];
	this->nextPosition = new int[this->capacity];

	this->firstEmpty = 0; // list is empty
	for (int i = 0; i < this->capacity - 1; i++) {
		this->nextPosition[i] = i + 1;
	}
	this->nextPosition[this->capacity - 1] = -1;

	this->head = -1; // list is empty => there is no head
	this->nrElements = 0;
}

int Matrix::nrLines() const {
	return this->numberOfLines;
}

int Matrix::nrColumns() const {
	return this->numberOfColumns;
}

TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	return NULL_TELEM;
}

Matrix::~Matrix(){
	// SLLA destructor
	delete[] this->elements;
	delete[] this->nextPosition;
}


