#include "Matrix.h"
#include <exception>
#include <iostream>
using namespace std;

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

void Matrix::resizeLists(){
	MatrixElement* auxList1 = new MatrixElement[this->capacity * 2];
	int* auxList2 = new int[this->capacity * 2];

	for (int i = 0; i < this->capacity; i++) {
		auxList1[i] = this->elements[i];
		auxList2[i] = this->nextPosition[i];
	}
	for (int i = this->capacity; i < this->capacity * 2 - 1; i++) {
		auxList2[i] = i + 1;
	}
	auxList2[this->capacity * 2 - 1] = -1;
	firstEmpty = this->capacity;
	this->capacity *= 2;

	delete this->elements;
	delete this->nextPosition;
	this->elements = auxList1;
	this->nextPosition = auxList2;
}

void Matrix::independentListsCopy(const Matrix& newMatrix){
	if (newMatrix.capacity != this->capacity) {
		delete this->elements;
		delete this->nextPosition;

		this->elements = new MatrixElement[newMatrix.capacity];
		this->nextPosition = new int[newMatrix.capacity];
	}

	for (int i = 0; i < newMatrix.capacity; i++) {
		this->elements[i] = newMatrix.elements[i];
		this->nextPosition[i] = newMatrix.nextPosition[i];
	}
}

void Matrix::insertAfterPosition(const MatrixElement& currentElement, int position){
	this->nrElements++;
	if (this->nrElements == this->capacity) {
		resizeLists();
	}

	int newPosition = firstEmpty;
	firstEmpty = this->nextPosition[firstEmpty];
	this->elements[newPosition] = currentElement;

	if (position == -1) { // new head
		this->nextPosition[newPosition] = this->head;
		this->head = newPosition;
	}
	else {
		this->nextPosition[newPosition] = this->nextPosition[position];
		this->nextPosition[position] = newPosition;
	}
}

void Matrix::removeElementAfterPosition(int position){
	this->nrElements--;
	int removedPosition = head;

	if (position == -1) {
		removedPosition = head;
		head = nextPosition[head];
	}
	else {
		removedPosition = nextPosition[position];
		nextPosition[position] = nextPosition[nextPosition[position]];
	}
	nextPosition[removedPosition] = firstEmpty;
	firstEmpty = removedPosition; // the removed position (nextPos[pos]) is marked as empty
}

bool Matrix::validPosition(int row, int column) const{
	return row >= 0 and row < this->numberOfLines and column >= 0 and column < this->numberOfColumns;
}

bool Matrix::elementSmallerThan(const MatrixElement& currentElement, int i, int j) const{
	return currentElement.line < i or (currentElement.line == i and currentElement.column < j);
}

bool Matrix::elementEqualTo(const MatrixElement& currentElement, int i, int j) const{
	return currentElement.line == i and currentElement.column == j;
}

bool Matrix::foundExactElement(int position, int i, int j) const {
	return position != -1 and elementEqualTo(this->elements[position], i, j);
}

int Matrix::getPositionSmallerThan(int i, int j) const {
	int currentPosition = this->head;

	if (this->head == -1 or !elementSmallerThan(elements[head], i, j)) {
		return -1;
	}

	while (nextPosition[currentPosition] != -1 and elementSmallerThan(elements[nextPosition[currentPosition]], i, j)) {
		currentPosition = nextPosition[currentPosition];
	}
	return currentPosition;
}

int Matrix::nrLines() const {
	return this->numberOfLines;
}

int Matrix::nrColumns() const {
	return this->numberOfColumns;
}

TElem Matrix::element(int i, int j) const {
	if (this->validPosition(i, j) == false) {
		throw std::exception("Invalid position");
	}

	int previousPosition = getPositionSmallerThan(i, j);
	int actualPosition;
	if (previousPosition == -1) {
		actualPosition = this->head;
	}
	else {
		actualPosition = nextPosition[previousPosition];
	}
	if (foundExactElement(actualPosition, i, j) == false) {
		return 0;
	}
	return this->elements[actualPosition].value;
}

TElem Matrix::modify(int i, int j, TElem e) {
	if (this->validPosition(i, j) == false) {
		throw std::exception("Invalid position");
	}

	MatrixElement currentElement{ i, j, e };
	int previousPosition = getPositionSmallerThan(i, j);
	int actualPosition;
	if (previousPosition == -1) {
		actualPosition = this->head;
	}
	else {
		actualPosition = nextPosition[previousPosition];
	}

	if (foundExactElement(actualPosition, i, j) == true) {
		int previousValue;
		previousValue = this->elements[actualPosition].value;
		if (e == NULL_TELEM) {
			this->removeElementAfterPosition(previousPosition);
		}
		else {
			this->elements[actualPosition] = currentElement;
		}
		return previousValue;
	}
	else if (e != NULL_TELEM){
		this->insertAfterPosition(currentElement, previousPosition);
	}
	return NULL_TELEM;
}

Matrix& Matrix::operator = (const Matrix& originalMatrix){
	if (this != &originalMatrix) {
		this->capacity = originalMatrix.capacity;
		this->head = originalMatrix.head;
		this->firstEmpty = originalMatrix.firstEmpty;
		this->nrElements = originalMatrix.nrElements;
		this->numberOfLines = originalMatrix.numberOfLines;
		this->numberOfColumns = originalMatrix.numberOfColumns;
		this->independentListsCopy(originalMatrix);
	}

	return *this;
}

Matrix::Matrix(const Matrix& originalMatrix){
	this->capacity = originalMatrix.capacity;
	this->head = originalMatrix.head;
	this->firstEmpty = originalMatrix.firstEmpty;
	this->nrElements = originalMatrix.nrElements;
	this->numberOfLines = originalMatrix.numberOfLines;
	this->numberOfColumns = originalMatrix.numberOfColumns;
	this->independentListsCopy(originalMatrix);
}

Matrix::~Matrix(){
	// SLLA destructor
	delete[] this->elements;
	delete[] this->nextPosition;
}


