/*
File:			BST.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A binary search tree
Notes:			Property of Full Sail University 2310
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <string>

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
#define LAB_7	1

// Individual unit test toggles
#define BST_CTOR								1
#define BST_NODE_CTOR							1
#define BST_PUSH_EMPTY							1
#define BST_PUSH_LEFT							1
#define BST_PUSH_RIGHT							1
#define BST_CLEAR								1
#define BST_DTOR								1
#define BST_CONTAINS_FOUND						1
#define BST_CONTAINS_NOTFOUND					1
#define BST_REMOVE_CASE0_ROOT					1
#define BST_REMOVE_CASE0_LEFT					1
#define BST_REMOVE_CASE0_RIGHT					1
#define BST_REMOVE_CASE1_ROOT_LEFT				1
#define BST_REMOVE_CASE1_ROOT_RIGHT				1
#define BST_REMOVE_CASE1_LEFT_LEFT				1
#define BST_REMOVE_CASE1_LEFT_RIGHT				1
#define BST_REMOVE_CASE1_RIGHT_LEFT				1
#define BST_REMOVE_CASE1_RIGHT_RIGHT			1
#define BST_REMOVE_CASE2_CASE0					1
#define BST_REMOVE_CASE2_CASE1					1
#define BST_REMOVE_CASE0						1
#define BST_REMOVE_CASE1						1
#define BST_REMOVE_CASE2						1
#define BST_REMOVE_NOT_FOUND					1
#define BST_IN_ORDER_TRAVERSAL					1
#define BST_ASSIGNMENT_OP						1
#define BST_COPY_CTOR							1


// Templated binary search tree
template<typename Type>
class BST {

	friend class UnitTests_Lab7;	// Giving access to test code

	struct Node 
	{
		Type data;					
		Node* left, * right;		
		Node* parent;				

			Node(const Type& _data, Node* _parent = nullptr) 
			{
				data = _data;
				parent = _parent;
				this->left = nullptr;
				this->right = nullptr;
			}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Node* mRoot = reinterpret_cast<Node*>(-1);	// Pointer to the root (top) node

public:

	BST() 
	{
		mRoot = nullptr;
	}

	~BST() 
	{
		Clear(mRoot);
		mRoot = nullptr;
	}

	BST(const BST& _copy) 
	{
		mRoot = nullptr;
		mRoot = Copy(_copy.mRoot);
	}

	BST& operator=(const BST& _assign) 
	{
		if (this == &_assign) { return *this; }

		Clear();

		mRoot = nullptr;	
		mRoot = Copy(_assign.mRoot);

		return *this;
	}

private:
	// Recursive helper method for use with Rule of 3
	Node* Copy(const Node* _curr) 
	{
		// Check if the current node from the orginal tree is null
		if (_curr == nullptr)
		{
			return nullptr;
		}
		
		Node* newNode = new Node(_curr->data);

		newNode->left = Copy(_curr->left);
		newNode->right = Copy(_curr->right);

		return newNode;
	}

public:

	void Clear() 
	{
		Clear(mRoot);
		mRoot = nullptr;
	}

private:

	// Recursive helper method for use with Clear
	void Clear(Node* _curr) 
	{
		// Check if the current node from the orginal tree is null
		if (_curr == nullptr)
		{
			return;
		}

		Clear(_curr->left);
		Clear(_curr->right);

		delete _curr;
	}

public:

	void Push(const Type& _val) 
	{
		Node* newNode = new Node(_val);
		
		Node* current = mRoot;
		Node* marker = nullptr;

		if (mRoot == nullptr) // if tree is empty
		{
			mRoot = newNode;
			return;
		}

		while (current != nullptr) 
		{
			marker = current; // starting point

			if (_val > current->data)
			{
				current = current->right;
			}
			else if (_val < current->data)
			{
				current = current->left;
			}
			else
			{
				return;
			}
		}

		newNode->parent = marker; // after find spot, set marker to newNode parent
		
		if (marker != nullptr)
		{
			if (newNode->data > marker->data) { marker->right = newNode; }
			else if (newNode->data < marker->data) { marker->left = newNode; }
		}
	}

	bool Contains(const Type& _val) 
	{
		Node* temp = mRoot;

		while (temp != nullptr)
		{
			if (_val == temp->data) // val = mRoot 
			{
				return true;
			}
			else if (_val < temp->data)
			{
				temp = temp->left;
			}
			else // _val > temp->data;
			{
				temp = temp->right;
			}
		}

		return false;
	}

private:

	Node* FindNode(const Type& _val)
	{
		Node* temp = mRoot;

		while (temp != nullptr)
		{
			if (_val == temp->data) // val = mRoot 
			{
				return temp;
			}
			else if (_val < temp->data)
			{
				temp = temp->left;

				if (temp != nullptr && _val == temp->data) {return temp; }
			}
			else // _val > temp->data;
			{
				temp = temp->right;
				if (temp != nullptr && _val == temp->data) { return temp; }
			}
		}

		return nullptr;
	}

	void RemoveCase0(Node* _node) 
	{
		if (_node == mRoot)
		{
			delete mRoot;
			mRoot = nullptr;
		}
		else if (_node->parent->left == _node)
		{
			_node->parent->left = nullptr;
			delete _node;
		}
		else if (_node->parent->right == _node)
		{
			_node->parent->right = nullptr;
			delete _node;
		}
	}

	void RemoveCase1(Node* _node) 
	{
		if (_node == nullptr) {
			return;  // Exit if node is null
		}

		// Temporarily store the child of _node
		Node* child = (_node->left != nullptr) ? _node->left : _node->right;

		if (_node->parent != nullptr) {  // The node is not the root
			// Update the parent's child pointer
			if (_node->parent->left == _node) {
				_node->parent->left = child;
			}
			else {
				_node->parent->right = child;
			}
		}
		else {  // The node is the root
			mRoot = child;
		}

		// Update the child's parent pointer
		if (child != nullptr) {
			child->parent = _node->parent;
		}

		// Delete the node
		delete _node;
	}

	void RemoveCase2(Node* _node) 
	{
		// Find the smallest node in the right subtree of _node
		Node* smallestInRightSubtree = _node->right;

		while (smallestInRightSubtree->left != nullptr) 
		{
			smallestInRightSubtree = smallestInRightSubtree->left;
		}

		_node->data = smallestInRightSubtree->data;

		if (smallestInRightSubtree->left != nullptr) 
		{
			RemoveCase1(smallestInRightSubtree);  // Has a left child
		}
		else if (smallestInRightSubtree->right != nullptr)
		{
			RemoveCase1(smallestInRightSubtree);  // Has a right child
		}
		else 
		{
			RemoveCase0(smallestInRightSubtree);  // Has no children
		}
	}

public:

	bool Remove(const Type& _val) 
	{
		// Step 1: Find the node to be removed
		Node* nodeToRemove = FindNode(_val);  // Assuming you have a method to find the node
		if (nodeToRemove == nullptr) {
			return false;  // Node not found, nothing to remove
		}

		// Step 2: Check the number of children
		int numChildren = 0;
		if (nodeToRemove->left != nullptr) numChildren++;
		if (nodeToRemove->right != nullptr) numChildren++;

		// Step 3: Call the appropriate RemoveCase method based on the number of children
		switch (numChildren) {
		case 0:
			RemoveCase0(nodeToRemove);  // No children
			break;
		case 1:
			RemoveCase1(nodeToRemove);  // One child
			break;
		case 2:
			RemoveCase2(nodeToRemove);  // Two children
			break;
		default:
			return false;  // Should never reach here
		}

		return true;  // Node was successfully removed
	}

	std::string InOrder() 
	{
		std::stringstream _str;  // String stream to store the space-delimited string	
		InOrderHelper(mRoot, _str);  // Start the In-Order traversal from the root

		std::string result = _str.str();

		// Remove the trailing space, if any
		if (!result.empty())
		{
			result.pop_back();
		}

		return result;
	}

private:

	// Recursive helper method to help with InOrder
	void InOrderHelper(Node* _curr, std::stringstream& _str)
	{
		if (_curr == nullptr) { return; }

		InOrderHelper(_curr->left, _str);  // Visit the left subtree

		// Visit the current node
		_str << std::to_string(_curr->data) << " ";  // Convert the integer to string and append to ss

		InOrderHelper(_curr->right, _str);  // Visit the right subtree
	}
};

