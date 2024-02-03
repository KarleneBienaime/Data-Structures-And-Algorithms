/*
File:			Lab2.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		Usage of the std::vector class
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
#define LAB_2	1

// Individual unit test toggles
#define LAB2_PALINDROME_NUMBER		1
#define LAB2_FILL_FILE				1
#define LAB2_FILL_ARRAY				1
#define LAB2_CLEAR					1
#define LAB2_SORT_ASCENDING			1
#define LAB2_SORT_DESCENDING		1
#define LAB2_BRACKETS				1
#define LAB2_CONTAINS_TRUE			1
#define LAB2_CONTAINS_FALSE			1
#define LAB2_MOVE_PALINDROMES		1

/************/
/* Includes */
/************/
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>


inline int IsPalindromeNumber(unsigned int _num) 
{
	std::vector<size_t> digits;
	while (_num > 0)
	{
		int cur_digit = _num % 10;
		digits.push_back(cur_digit);
		_num /= 10;
	}

	std::vector<size_t> reversed_digits = digits;
	std::reverse(begin(reversed_digits), end(reversed_digits));

	return digits == reversed_digits;
}

class DSA_Lab2
{
	friend class UnitTests_Lab2;	// Giving access to test code

private:

	std::vector<int> mValues;		// contains all of the values
	std::vector<int> mPalindromes;	// contains just the numbers that are palindromes (only used in MovePalindromes method)

public:

	void Fill(const char* _inputFilename) 
	{
		// Open the file located at in binary read mode.
		std::ifstream file(_inputFilename, std::ios::binary);

		// Read the four-byte header from the file.
		char Data[1025];
		file.read(Data, sizeof(Data));

		// Interpret the 4-byte header as an integer.
		int temp;
		std::memcpy(&temp, Data, sizeof(temp));

		// Resize the vector to accommodate the new data.
		mValues.resize(temp);

		// Read the specified number of bytes/values from the file into the vector.
		file.read(reinterpret_cast<char*>(mValues.data()), temp);
		file.close();
	}

	void Fill(const int* _arr, size_t _size) 
	{
		for (size_t i = 0; i < _size; i++) 
		{
			mValues.push_back(_arr[i]);
		}
	}

	void Clear() 
	{
		// Removes all elements from the values vector
		mValues.clear();
		mValues.shrink_to_fit();
	}

	void Sort(bool _ascending) 
	{
		if (_ascending == true)
		{
			std::sort(mValues.begin(), mValues.end());
		}
		else
		{
			std::sort(mValues.begin(), mValues.end());
			std::reverse(mValues.begin(), mValues.end());
		}
	}

	int operator[](int _index) 
	{
		return mValues[_index];
	}

	bool Contains(int _val) const 
	{
		for ( auto element : mValues)
		{
			if (element == _val) 
			{
				return true;
			}
		}
		return false;
	}

	void MovePalindromes() 
	{	
		std::vector<int> temp;

		//	o Iterate through the values vector
		for (auto i = 0; i < mValues.size(); i++)	
		{
			bool isPalindrome = IsPalindromeNumber(mValues[i]);

			//	▪ If the value is a palindrome(remember you have a method to check this)
			if (isPalindrome == true)
			{
				//	• Add it to the palindromes vector
				mPalindromes.push_back(mValues[i]);
				//	• Remove it from the values vector
			}
			else
			{
				temp.push_back(mValues[i]);
			}
		}

		mValues = temp;
	}
};

