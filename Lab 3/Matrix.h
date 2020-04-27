#pragma once

//DO NOT CHANGE THIS PART
#define NULL_TELEM 0
#define INITIAL_CAPACITY 100
typedef int TElem;

struct MatrixElement {
	int line;
	int column;
	TElem value;
};

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

		void resizeLists();
		void insertAfterPosition(MatrixElement currentElement, int position);
		void removeElement(int position); // happens when we add sth with value == 0
		bool validPosition(int row, int column) const;
		bool elementSmallerThan(MatrixElement currentElement, int i, int j) const;
		bool elementEqualTo(MatrixElement currentElement, int i, int j) const;
		bool foundExactElement(int previousPosition, int i, int j) const;
		int getPositionSmallerThan(int i, int j) const;

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
