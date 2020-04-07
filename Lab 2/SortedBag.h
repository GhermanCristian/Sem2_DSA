#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

struct Node {
	TComp info;
	int nrOfOccurences;
	Node* nextNode;
	Node* prevNode;
};

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

	private:
		Node* head; // first node in the list
		Node* tail; // last node in the list
		Relation currentRelation;
		int listLength; // how many nodes in the list (<=> how many different elements)
		int nrOfElements; // total elements (including duplicates)
		
		void insertBeforeNode(Node* rightNode, TComp info);
		/*
			Inserts a new node before a given node
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The node before we need to insert (which can be nullptr, signifying that we append to the list)
				- The information of the new node
			Output:
				- The new node is added to the list at the given position
		*/

		Node* getNodeWithInfo(TComp info) const;		
		/*
			Determines the node which contains some information, or the one which would have been right after it (if
			it doesn't exist)
			Complexity:
				- BC: theta(1), when the element is on the first position
				- AC: theta(n)
				- WC: theta(n), when the element is on the last position
			Input:
				- The information of the node we search for
			Output:
				- The required node (can be nullptr if we don't find anything)
		*/

		bool foundExactElement(Node* possiblePosition, TComp info) const;
		/*
			Determines if a given node contains exactly the information that we want
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The node which might hold the information that we want
				- The information that we want
			Output:
				- True, if the information coincides
				- False, otherwise
		*/

		void independentCopyOfList(const SortedBag& originalSortedBag);
		/*
			Copies, one-by-one, all the elements from the list of another SortedBag to the current one
			Complexity:
				- BC/AC/WC: theta(n), n = current length of the list
			Input:
				- The SortedBag we copy from
			Output:
				- The content of that SortedBag is independently copied to the current one (new Nodes, but the same
				information)
		*/

		bool removeFromListWithOneElement(TComp e);
		/*
			Removes an instance of an element from a one-element-list
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The information of the element that we want to remove
			Output:
				- True, if the element existed, in which case the instance of the element is removed
				- False, otherwise
		*/

		void deleteNode(Node* elementPosition);
		/*
			Deletes a given Node and ensures the list isn't broken
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The node that we want to delete
			Output:
				- The node is deleted, the previous and next nodes are linked (if possible)
		*/

	public:
		SortedBag(Relation r);
		/*
			Constructor
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- The relation between the elements
			Output:
				- A new, empty object of type SortedBag is constructed
		*/

		void add(TComp e);
		/*
			Adds an element to the SortedBag
			Complexity:
				- BC: theta(1), when the element belongs on the first position
				- AC: theta(n)
				- WC: theta(n), when the element belongs on the last position
			Input:
				- The element that we want to add
			Output:
				- The element is added to the list
		*/

		bool remove(TComp e);
		/*
			Removes an instance of an element from the SortedBag
			Complexity:
				- BC: theta(1), when the element was on the first position
				- AC: theta(n)
				- WC: theta(n), when the element was on the last position, or it didn't exist
			Input:
				- The element that we want to remove
			Output:
				- Returns true, if the element existed, in which case it is removed from the list
				- False, otherwise
		*/

		bool search(TComp e) const;
		/*
			Searches for an element in the SortedBag
			Complexity:
				- BC: theta(1), when the element is on the first position
				- AC: theta(n)
				- WC: theta(n), when the element is on the last position, or it's not int the list
			Input:
				- The element that we search for
			Output:
				- Returns true, if the element exists
				- False, otherwise
		*/

		int nrOccurrences(TComp e) const;
		/*
			Determines the number of occurences of an element in the SortedBag
			Complexity:
				- BC: theta(1), when the element is on the first position in the list
				- AC: theta(n)
				- WC: theta(n), when the element is on the last position, or it's not int the list
			Input:
				- The element whose number of occurences we want to determine
			Output:
				- Returns the number of occurences of the given element (or 0, if it doesn't exist)
		*/

		int size() const;
		/*
			Determines the size of the SortedBag
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- None
			Output:
				- Returns the size of the SortedBag
		*/

		SortedBagIterator iterator() const;
		/*
			Returns an iterator of the SortedBag
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- None
			Output:
				- Returns an iterator of the SortedBag
		*/

		bool isEmpty() const;
		/*
			Checks if the SortedBag is empty
			Complexity:
				- BC/AC/WC: theta(1)
			Input:
				- None
			Output:
				- Returns true, if the SortedBag is empty
				- False, otherwise
		*/

		SortedBag(const SortedBag& originalSortedBag);
		/*
			Copy constructor
			Complexity:
				- BC/AC/WC: theta(n), n = current length of the list of elements from the SortedBag
			Input:
				- The SortedBag we copy from
			Output:
				- The content of that SortedBag is copied to the current one
		*/

		SortedBag& operator = (const SortedBag& originalSortedBag);
		/*
			Assignment operator
			Complexity:
				- BC/AC/WC: theta(n), n = current length of the list of elements from the SortedBag
			Input:
				- The SortedBag we copy from
			Output:
				- The content of that SortedBag is copied to a new one, which is returned
		*/

		~SortedBag();
		/*
			Destructor
			Complexity:
				- BC/AC/WC: theta(n), n = current length of the list of elements from the SortedBag
			Input:
				- None
			Output:
				- Destroys the current SortedBag
		*/
};