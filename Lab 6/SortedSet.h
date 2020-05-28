#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111
class SortedSetIterator;

const int INITIAL_CAPACITY = 127; // 7 levels
const int NONEXISTENT_POSITION = -1;

struct Node {
	TComp info;
	int left;
	int right;
	int parent;
};
const Node NULL_NODE = { NULL_TELEM, NONEXISTENT_POSITION, NONEXISTENT_POSITION, NONEXISTENT_POSITION }; // it should be NULL_TCOMP but I don't have that

class SortedSet {
	friend class SortedSetIterator;

	private:
		Node* elements;
		int elementCount;
		int arrayCapacity;
		Relation relation;
		int rootPosition;
		int* nextEmpty;
		int firstEmpty; // index of the first empty position (used in nextEmpty)

		int findPositionOf(TComp elem) const;
		void addNewNode(TComp elem, int position, bool isLeftChild, int parentPosition);
		void resizeArray();

	public:
		//constructor
		SortedSet(Relation r);

		//adds an element to the sorted set
		//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
		//it returns false
		bool add(TComp e);

		//removes an element from the sorted set
		//if the element was removed, it returns true, otherwise false
		bool remove(TComp e);

		//checks if an element is in the sorted set
		bool search(TComp elem) const;

		//returns the number of elements from the sorted set
		int size() const;

		//checks if the sorted set is empty
		bool isEmpty() const;

		//returns an iterator for the sorted set
		SortedSetIterator iterator() const;

		// destructor
		~SortedSet();
};
