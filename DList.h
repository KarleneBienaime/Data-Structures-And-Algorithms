/*
File:			DList.h\
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A doubly-linked list (similar to std::list)
Notes:			Property of Full Sail University 2310
*/

// Header protection
#pragma once

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/


// Main toggle
#define LAB_3	1

// Individual unit test toggles			
#define LAB3_CTOR						1
#define LAB3_NODE_CTOR_DEFAULT			1
#define LAB3_NODE_CTOR					1
#define LAB3_ADDHEAD_EMPTY				1
#define LAB3_ADDHEAD					1
#define LAB3_ADDTAIL_EMPTY				1
#define LAB3_ADDTAIL					1
#define LAB3_CLEAR						1
#define LAB3_DTOR						1
#define LAB3_ITER_BEGIN					1
#define LAB3_ITER_END					1
#define LAB3_ITER_INCREMENT_PRE			1
#define LAB3_ITER_INCREMENT_POST		1
#define LAB3_ITER_DECREMENT_PRE			1
#define LAB3_ITER_DECREMENT_POST		1
#define LAB3_ITER_DEREFERENCE			1
#define LAB3_INSERT_EMPTY				1
#define LAB3_INSERT_HEAD				1
#define LAB3_INSERT_MIDDLE				1
#define LAB3_ERASE_EMPTY				1
#define LAB3_ERASE_HEAD					1
#define LAB3_ERASE_TAIL					1
#define LAB3_ERASE_MIDDLE				1
#define LAB3_ASSIGNMENT_OP				1
#define LAB3_COPY_CTOR					1

template<typename Type>
class DList {

	friend class UnitTests_Lab3;	// Giving access to test code

	struct Node 
	{
		// NOTE: Values set to -1 for unit test purposes
		Type data;
		Node* next = reinterpret_cast<Node*>(-1);
		Node* prev = reinterpret_cast<Node*>(-1);

	
		Node(const Type& _data, Node* _next = nullptr, Node* _prev = nullptr) 
		{
			// Set the data members to the values of the parameters passed in

			data = _data;	// The value being stored (think of the “element” in an array)
			next = _next;	// A pointer to the next node in the list
			prev = _prev;	// A pointer to the previous node in the list
		}
	};

public:

	class Iterator 
	{
	public:

		Node* mCurr = nullptr;

		Iterator& operator++() // pre ++
		{
			// Moves the Iterator to the next node in the list and returns it
			mCurr = mCurr->next;
			return *this;	
		}

		Iterator operator++(int) // post ++
		{
			// Post-fix operators take in an int to allow the compiler to differentiate
			// Moves the Iterator to the next node in the list and return an Iterator to the original position
			Iterator temp(mCurr);
			mCurr = mCurr->next;
			return temp;
			// This will require a temporary variable
		}

		Iterator& operator--() // pre ++
		{
			// Moves the Iterator to the previous node in the list and returns it
			mCurr = mCurr->prev;
			return *this;
		}

		Iterator operator--(int) // post ++
		{
			// Post-fix operators take in an int to allow the compiler to differentiate
			// Moves the Iterator to the previous node in the list and return an Iterator to the original position
			Iterator temp(mCurr);
			mCurr = mCurr->prev;
			return temp;
			// This will require a temporary variable
		}

		Type& operator*() 
		{
			// Return the data of the node the Iterator is pointing to
			return mCurr->data;	
		}

		bool operator != (const Iterator& _iter) const  
		{
			return mCurr != _iter.mCurr;
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Node* mHead = reinterpret_cast<Node*>(-1); 		// mHead A pointer to the “front” Node in the list
	Node* mTail = reinterpret_cast<Node*>(-1);		// mTail A pointer to the “back” Node in the list
	size_t mSize = 0;								// mSize The current number of Nodes allocated

public:

	DList() 
	{
		// Set all data members to reflect that NO nodes are currently allocated
		mHead = nullptr;
		mTail = nullptr;
		mSize = 0;
	}

	~DList() 
	{
		// Free up the memory for all dynamically 
		// allocated nodes (There’s a method that does this)
		Clear();
	}

	DList(const DList& _copy)  
	{
		// Initialize the list to an empty state
		mHead = nullptr;
		mTail = nullptr;
		mSize = 0;

		// Start at the head of the list to be copied
		Node* assignCurr = _copy.mHead;

		while (assignCurr)
		{
			// Create a new node with the data from the _copy list
			Node* newNode = new Node(assignCurr->data);

			// If this is the first node, set it as the head
			if (!mHead)
			{
				mHead = newNode;
				mTail = newNode;
			}
			else
			{
				// Otherwise, append the node to the tail and update the tail
				mTail->next = newNode;
				newNode->prev = mTail;
				mTail = newNode;
			}

			// Move to the next node in the _copy list
			assignCurr = assignCurr->next;

			// Increment the size
			mSize++;
		}
	}

	DList& operator=(const DList& _assign) 
	{
		// Check for self-assignment
		if (this == &_assign) {
			return *this;
		}

		// Clean up existing memory before the deep copy
		Clear();

		// Initialize the list to an empty state
		mHead = nullptr;
		mTail = nullptr;
		mSize = 0;

		// Start at the head of the list to be copied
		Node* assignCurr = _assign.mHead;

		while (assignCurr) {
			// Create a new node with the data from the _assign list
			Node* newNode = new Node(assignCurr->data);

			// If it's the first node, set it as the head
			if (!mHead) {
				mHead = newNode;
				mTail = newNode;
			}
			else {
				// Otherwise, append the node to the tail and update the tail
				mTail->next = newNode;
				newNode->prev = mTail;
				mTail = newNode;
			}

			// Move to the next node in the _assign list
			assignCurr = assignCurr->next;

			// Increment the size
			mSize++;
		}

		return *this;
	}

	void AddHead(const Type& _data) 
	{
		// Dynamically add a Node to the front of the list
		Node* newHead = new Node(_data);

		if (mHead == nullptr)
		{
			mHead = newHead;  // Set the new node as the head
			mTail = newHead;
		}
		else
		{
			newHead->next = mHead; // New head's next is not pointing to old head
			mHead->prev = newHead; // Old head's prev is not pointing to new head
			mHead = newHead;
		}
		mSize++;
	}

	void AddTail(const Type& _data) 
	{
		// Dynamically add a Node to the front of the list
		Node* newTail = new Node(_data);

		if (mTail == nullptr)
		{
			mTail = newTail;  // Set the new node as the head
			mHead = newTail;
		}
		else 
		{
			newTail->prev = mTail;
			mTail->next = newTail;
			newTail->next = nullptr;
			mTail = newTail;
		}
		mSize++;
	}

	void Clear() 
	{
		// Free up the memory for all dynamically allocated nodes
		// • Set all of the data members back to their default state

		Node* mCurr = mHead;	// Start at first node
		while (mCurr)
		{
			Node* temp = mCurr->next;	// temp points to next node
			delete mCurr;				// delete current
			mCurr = temp;				// move to next node
		}

		mHead = nullptr; // reset data menbers
		mTail = nullptr;
		mSize = 0;

	}

	Iterator Insert(Iterator& _iter, const Type& _data)
	{
		Node* newNode = new Node(_data);

		// Empty List:
		if (!_iter.mCurr) {
			mHead = newNode;
			mTail = newNode;
		}
		// Inserting at the Head:
		else if (_iter.mCurr == mHead) {
			newNode->next = mHead;
			mHead->prev = newNode;
			mHead = newNode;
		}
		// Inserting Anywhere Else:
		else {
			Node* nodeBefore = _iter.mCurr->prev;
			Node* nodeAfter = _iter.mCurr;

			newNode->prev = nodeBefore;
			newNode->next = nodeAfter;
			nodeBefore->next = newNode;
			nodeAfter->prev = newNode;
		}

		_iter.mCurr = newNode;  // Updating the iterator to point to the new node.
		mSize++;
		return _iter;  // Return iterator pointing to the new node.
	}

	Iterator Erase(Iterator& _iter) 
	{
		// If there's nothing to erase or if the iterator isn't pointing to any valid node
		if (!_iter.mCurr) {
			return _iter;
		}

		// Handling if the current node is the head
		if (_iter.mCurr == mHead) {
			mHead = _iter.mCurr->next;
			if (mHead) {
				mHead->prev = nullptr;
			}
			else {
				mTail = nullptr;  // If head was the only node, set tail to nullptr as well
			}
		}
		// Handling if the current node is the tail (but not head, since that's already handled)
		else if (_iter.mCurr == mTail) {
			mTail = _iter.mCurr->prev;
			if (mTail) {
				mTail->next = nullptr;
			}
		}
		// Handling for nodes in the middle
		else {
			_iter.mCurr->prev->next = _iter.mCurr->next;
			_iter.mCurr->next->prev = _iter.mCurr->prev;
		}

		Node* nextNode = _iter.mCurr->next;
		delete _iter.mCurr;  // Delete the current node
		mSize--;  // Decrement the size of the list

		return Iterator(nextNode);  // Return an iterator pointing to the next node
	}

	Iterator Begin() const 
	{
		// • Creates and returns an Iterator that points to the head node
		Node* Begin = nullptr;
		Begin = mHead;
		return Iterator(Begin);
	}

	Iterator End() const 
	{
		// Creates and returns an Iterator that points to the Node after the last valid node in the list
		Node* End = nullptr;
		End = mTail;
		return Iterator(nullptr);
	}
};