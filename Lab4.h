/*
File:			DSA_Lab4.h	
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		Usage of the std::list class
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
#define LAB_4	1

// Individual unit test toggles
#define LAB4_QUEUE_ADD			1
#define LAB4_STACK_ADD			1
#define LAB4_QUEUE_REMOVE		1
#define LAB4_STACK_REMOVE		1
#define LAB4_INSERT_ITER		1
#define LAB4_INSERT_INDEX		1
#define LAB4_REMOVE_DECIMAL		1

/************/
/* Includes */
/************/
#include <list>

class DSA_Lab4 {

	friend class UnitTests_Lab4;	// Giving access to test code

	// Data members
	std::list<float> mList;

public:

	void QueueOrderingAdd(const float* _arr, size_t _size) 
	{
		for (size_t i = 0; i < _size; i++)
		{
			mList.push_back(_arr[i]);
		}
	}

	void StackOrderingAdd(const float* _arr, size_t _size) 
	{
		for (size_t i = 0; i < _size; i++)
		{
			mList.push_front(_arr[i]);
		}
	}

	float QueueOrderingRemove() 
	{
		// The front of the queue is the oldest item, and the back is the newest.
		float first = mList.front();
		mList.pop_front();
		return first;
	}

	float StackOrderingRemove() 
	{
		// The back of the stack is the newest item, and the front is the oldest.
		float first = mList.front();
		mList.pop_front();
		return first;
	}

	void Insert(int _index, float _val) 
	{
		// Start from the beginning of the list
		auto it = mList.begin();

		// Advance the iterator to the desired position
		std::advance(it, _index);

		// Now insert the value at that position
		mList.insert(it, _val);
	}

	void Insert(std::list<float>::iterator _iter, float _val) 
	{
		mList.insert(_iter, _val);
	}

	int RemoveDecimalGreater(float _decimal) 
	{
		int removedCount = 0; // Keeps track of how many numbers we've removed

		std::list<float>::iterator iter = mList.begin(); // Declare an iterator of type 'float' for the list

		while (iter != mList.end())
		{
			// Extracting the integer part from the number (like 1 from 1.5)
			int integerPart = static_cast<int>(*iter);

			// Finding the decimal part of the number (like 0.5 from 1.5)
			float decimalPart = *iter - integerPart;

			// Check if the decimal part is bigger than our given limit (threshold)
			if (decimalPart > _decimal)
			{
				// If yes, remove this number from the list
				iter = mList.erase(iter);

				// Count the removal
				removedCount++;
			}
			else
			{
				// If the decimal part isn't too big, just move on to the next number
				++iter;
			}
		}

		// Return the amount of numbers that were removed
		return removedCount;
	}
};