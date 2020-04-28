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
		int head; // index of the first element in the list
		int firstEmpty; // index of the first empty position in the list
		int nrElements;

		int numberOfLines;
		int numberOfColumns;

		void resizeLists();
		/*
			Resizes the lists of the Matrix
			Complexity:
				- BC/AC/WC: theta(n)
			Input:
				- None
			Output:
				- The size of the lists is doubled
		*/

		void independentListsCopy(const Matrix& newMatrix);
		/*
			Copies the content of the lists from another Matrix to the current one
			Complexity:
				- BC/AC/WC: theta(n)
			Input:
				- The Matrix we copy from
			Output:
				- The content is copied (and the lists are resized if necessary)
		*/

		void insertAfterPosition(const MatrixElement& currentElement, int position);
		/*
			Inserts the element after a given position
			Complexity:
				- BC/AC/WC: theta(1) amortized (when the list is full, it needs to resize, in theta(n))
			Input:
				- The element we want to insert
				- The position we want to insert after
			Output:
				- The element is inserted in the list
		*/

		void removeElementAfterPosition(int position);
		/*
			Removes the element after the given position
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The position of the element before the one we want to remove
			Output:
				- The element is removed from the list
		*/

		bool validPosition(int row, int column) const;
		/*
			Checks if a pair of coordinates represents a valid position in the matrix
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The two coordinates
			Output:
				- Returns true if the coordinates are valid, and false otherwise
		*/

		bool elementSmallerThan(const MatrixElement& currentElement, int i, int j) const;
		/*
			Checks if the coordinates of a MatrixElement are lexicographically smaller than another pair of coordinates
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The element we want to compare
				- The coordinates we compare against
			Output:
				- Returns true if the MatrixElement is "smaller" than the pair of coordinates, and false otherwise
		*/

		bool elementEqualTo(const MatrixElement& currentElement, int i, int j) const;
		/*
			Checks if the coordinates of a MatrixElement are equal to another pair of coordinates
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The element we want to compare
				- The coordinates we compare against
			Output:
				- Returns true if the MatrixElement is equal to the pair of coordinates, and false otherwise
		*/

		bool foundExactElement(int previousPosition, int i, int j) const;
		/*
			Checks if the element on the given position has the same coordinates as the ones we searched for
			(because the search function looks for the largest position <= the given one)
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The position returned by the search
				- The two coordinates that we looked for
			Output:
				- Returns true if the two elements coincide, false otherwise
		*/

		int getPositionSmallerThan(int i, int j) const;
		/*
			Determines the largest position with an element whose coordinates are <= the given coordinates
			Complexity:
				- BC: theta(1), when the required position is the first one
				- AC: theta(n)
				- WC: theta(n), when the required position is the last one
			Input:
				- The coordinates of the element we compare against
			Output:
				- Returns the largest position .., or -1 if the head of the list has coordinates larger than
				the given element
		*/

	public:
		Matrix(int nrLines, int nrCols);
		/*
			Matrix constructor
			Complexity:
				- BC/AC/WC: theta(n)
			Input:
				- The number of lines and the number of columns of the Matrix
			Output:
				- The Matrix is built
		*/

		int nrLines() const;
		/*
			Returns the number of lines in the Matrix
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- None
			Output:
				- Returns the number of lines in the Matrix
		*/

		int nrColumns() const;
		/*
			Returns the number of columns in the Matrix
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- None
			Output:
				- Returns the number of columns in the Matrix
		*/

		TElem element(int i, int j) const;
		/*
			Determines the value of the element at the given coordinates in the Matrix
			Complexity:
				- BC: theta(1), when the element is on the first position in the list
				- AC: theta(n)
				- WC: theta(n), when the element is on the last position in the list
			Input:
				- The coordinates of the element
			Output:
				- Returns the value of the element at the given coordinates
				- Throws an error if the coordinates are invalid
		*/

		TElem modify(int i, int j, TElem e);
		/*
			Modifies the element at the given coordinates
			Complexity:
				- BC: theta(1), when the element is on the first position and we are not adding it to the list 
				(because the BC of the add function is theta(1) amortized, due to the possible list resizing)
				- AC: theta(n)
				- WC: theta(n), when the element is on the last position
			Input:
				- The coordinates of the element we want to update
				- The new value
			Output:
				- Returns the previous value of the element at the given coordinates
				- Throws an error if the coordinates are invalid
		*/

		Matrix& operator = (const Matrix& originalMatrix);
		/*
			Overloaded assignment operator
			Complexity:
				- BC: theta(1), when the given Matrix is the same as the current one
				- AC: theta(n)
				- WC: theta(n), when the two Matrices are different
			Input:
				- The Matrix we copy from
			Output:
				- Returns a reference to a Matrix object with the properties of the original one
		*/

		Matrix(const Matrix& originalMatrix);
		/*
			Matrix copy constructor
			Complexity:
				- BC/AC/WC: theta(n)
			Input:
				- The Matrix we copy from
			Output:
				- A new Matrix with the properties of the
		*/

		~Matrix();
		/*
			Matrix destructor
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- None
			Output:
				- The object is destroyed and the memory is deallocated
		*/
};
