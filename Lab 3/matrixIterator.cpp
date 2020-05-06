#include "matrixIterator.h"
#include "Matrix.h"
#include <exception>

MatrixIterator::MatrixIterator(const Matrix& crtMatrix, int line) : currentMatrix(crtMatrix){
	this->currentLine = line;
	first();
}

TElem MatrixIterator::getCurrent(){
	if (valid() == false) {
		throw exception("Invalid position");
	}
	return currentMatrix.element(this->currentLine, this->currentColumn);
}

bool MatrixIterator::valid(){
	return this->currentColumn >= 0 and this->currentColumn < currentMatrix.numberOfColumns;
}

void MatrixIterator::next(){
	if (valid() == false) {
		throw exception("Invalid position");
	}
	currentColumn++;
}

void MatrixIterator::first(){
	this->currentColumn = 0;
}
