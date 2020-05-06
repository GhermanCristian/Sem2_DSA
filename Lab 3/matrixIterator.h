#pragma once
#include "Matrix.h"

using namespace std;
class Matrix;

class MatrixIterator{
	friend class Matrix;

	private:
		int currentLine;
		int currentColumn;
		const Matrix& currentMatrix;
		MatrixIterator(const Matrix& crtMatrix, int line);

	public:
		TElem getCurrent();
		/*
			- BC : theta(1), when the element is on the first position in the line
			- AC : theta(n),
			- WC : theta(n), when the element is on the last position in the line
		*/
		// throws exception if the position is invalid
		
		bool valid(); 
		// checks if the current position is valid
		// BC/AC/WC: theta(1)

		void next();
		// advances to the next position; throws exception if there is not valid position left
		// BC/AC/WC: theta(1)
		// throws exception if the position is invalid

		void first();
		// sets the iterator on the first position
		// BC/AC/WC: theta(1)
};

