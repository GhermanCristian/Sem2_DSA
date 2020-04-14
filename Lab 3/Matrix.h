#pragma once
#include "matrixElement.h"

//DO NOT CHANGE THIS PART
#define NULL_TELEM 0
#define INITIAL_CAPACITY 100

class Matrix {
	private:
		MatrixElement* elements;
		int* nextPosition;
		int capacity;
		int head;
		int firstEmpty;
		int nrElements;

		int numberOfLines;
		int numberOfColumns;

		void insertElement(int line, int column, TElem value);
		void removeElement(int line, int column); // happens when we add sth with value == 0
		int getPositionLargerThan(TElem value);

	public:
		//constructor
		Matrix(int nrLines, int nrCols);

		//returns the number of lines
		int nrLines() const;

		//returns the number of columns
		int nrColumns() const;

		//returns the element from line i and column j (indexing starts from 0)
		//throws exception if (i,j) is not a valid position in the Matrix
		TElem element(int i, int j) const;

		//modifies the value from line i and column j
		//returns the previous value from the position
		//throws exception if (i,j) is not a valid position in the Matrix
		TElem modify(int i, int j, TElem e);

		~Matrix();
};
