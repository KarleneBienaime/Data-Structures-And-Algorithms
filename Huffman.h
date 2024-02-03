/*
File:			Huffman.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A class to wrap up Huffman compression algorithm
Notes:			Property of Full Sail University 2310
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <queue>
#include "BitStream.h"

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
#define LAB_8	1

// Individual unit test toggles
#define HUFFMAN_CTOR					1
#define HUFFMAN_GENERATE_FREQUENCY		1
#define HUFFMAN_GENERATE_LEAFLIST		1
#define HUFFMAN_GENERATE_TREE			1
#define HUFFMAN_CLEAR_TREE				1
#define HUFFMAN_DTOR					1
#define HUFFMAN_GENERATE_ENCODING		0
#define HUFFMAN_COMPRESS				0
#define HUFFMAN_DECOMPRESS				0

// Optional unit tests for debugging with small file containing "HELLO WORLD"
#define HUFFMAN_DEBUG_COMPRESS			0
#define HUFFMAN_DEBUG_DECOMPRESS		0

// Wraps up Huffman compression algorithm
class Huffman {

	friend class UnitTests_Lab8; // Giving access to test code

	// A node for a a Huffman tree
	struct HuffNode {
		short value;		 
		unsigned int freq;	
		HuffNode* left;		
		HuffNode* right;	
		HuffNode* parent;	

		HuffNode(short _value, unsigned int _freq, HuffNode* _left = nullptr, HuffNode* _right = nullptr, HuffNode* _parent = nullptr)
			: value(_value), freq(_freq), left(_left), right(_right), parent(_parent) {
		}

		HuffNode(const HuffNode& _hnode)
			: value(_hnode.value), freq(_hnode.freq), left(_hnode.left), right(_hnode.right), parent(_hnode.parent) {
		}
	};

	struct HuffCompare {
		bool operator() (const HuffNode* _a, const HuffNode* _b) {
			return(_a->freq > _b->freq);
		}
	};


	// Data members
	// NOTE: Values set to 1/-1 for unit test purposes
	std::string mFileName = "-1";						
	unsigned int mFrequencyTable[256] = { 1 };			
	std::vector<HuffNode*> mLeafList;					
	HuffNode* mRoot = reinterpret_cast<HuffNode*>(-1);	
	std::vector<bool> mEncodingTable[256];				


	Huffman(const std::string& _fileName) 
	{
		mFileName = _fileName;

		for (int i = 0; i < 256; ++i) {
			mFrequencyTable[i] = 0;
		}

		mRoot = nullptr;
	}

	~Huffman() {
		
		ClearTree();
	}


	void GenerateFrequencyTable() {
		
		// Declare an input file stream
		std::ifstream inFile;

		// Open the file in binary mode
		inFile.open(mFileName, std::ios::binary);

		// Declare a variable to store each byte read from the file
		char byte;

		// Read the file one byte at a time
		while (inFile.read(&byte, 1)) {
			// Increment the corresponding index in the frequency table
			// Note: 'byte' is automatically converted to its ASCII value when used as an array index
			mFrequencyTable[static_cast<unsigned char>(byte)]++;
		}

		// Close the file when complete
		inFile.close();

	}

	void GenerateLeafList() {
		
		// Loop through the entire frequency table
		for (int i = 0; i < 256; ++i) {
			// Check if the frequency of the current element is non-zero
			if (mFrequencyTable[i] != 0) {
				// Dynamically create a new HuffNode with the frequency and ASCII value
				HuffNode* newNode = new HuffNode(i, mFrequencyTable[i]);

				// Add the new node to the mLeafList vector
				mLeafList.push_back(newNode);
			}
		}
	}

	void GenerateTree() {
		
		// Create a priority_queue that stores HuffNode pointers in a vector and uses HuffCompare for sorting
		std::priority_queue<HuffNode*, std::vector<HuffNode*>, HuffCompare> pq;

		// Populate the priority_queue with data from the leaf list
		for (HuffNode* node : mLeafList) {
			pq.push(node);
		}

		// Generate the Huffman tree
		while (pq.size() > 1) { // Loop until there's only one node left in the queue
			// Store the top two nodes into temporary pointers and pop them from the queue
			HuffNode* first = pq.top(); pq.pop();
			HuffNode* second = pq.top(); pq.pop();

			// Create a new parent node with the first node as the left child and the second node as the right child
			// Set its value to -1 and its frequency to the sum of its two children's frequencies
			HuffNode* parent = new HuffNode(-1, first->freq + second->freq, first, second);

			// Set the parent pointers for the first and second nodes
			first->parent = parent;
			second->parent = parent;

			// Insert the new parent node back into the priority_queue
			pq.push(parent);
		}

		// Set the root data member, as there is now only one node left in the queue
		mRoot = pq.top(); pq.pop();
	}

	void GenerateEncodingTable() {
		

		
	}

	void ClearTree() {
		
		// Call the helper function starting at the root
		ClearTreeHelper(mRoot);

		// Set the root to nullptr to indicate that the tree is now empty
		mRoot = nullptr;
	
	}

	void ClearTreeHelper(HuffNode* _curr) {
		
		// Base case: if the node is nullptr, return
		if (_curr == nullptr) {
			return;
		}

		// Recur on the left subtree
		ClearTreeHelper(_curr->left);

		// Recur on the right subtree
		ClearTreeHelper(_curr->right);

		// Delete the current node
		delete _curr;
	
	}

	void Compress(const char* _outputFile) {
		

	}

	void Decompress(const char* _outputFile) {

		
	}
};

