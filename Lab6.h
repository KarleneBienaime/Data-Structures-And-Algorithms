/*
File:			DSA_Lab6.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:	Karlene Bienaime-Gruirrier

Purpose:		Usage of the std::unordered_map class
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
#define LAB_6	1

// Individual unit test toggles
#define LAB6_POPULATE_LETTER_VALUES	1
#define LAB6_GET_LETTER_VALUE		1
#define LAB6_GET_WORD_VALUE			1
#define LAB6_CREATE_PAIR			1
#define LAB6_LOAD_FILE				1
#define LAB6_FIND_WORD_SCORE		1


/************/
/* Includes */
/************/
#include <string>
#include <fstream>
#include <unordered_map>

class DSA_Lab6 {

	friend class UnitTests_Lab6;	// Giving access to test code

	// Data members
	int mLetterValues[26] = { -1 }; // Array of 26 values, representing the individual values for each letter
	std::unordered_map<std::string, int> mScrabbleMap; // stores the words as the key, and the total points as the value

public:

	void PopulateLetterValues(const int* _letterValues) 
	{
		// Copy the values of the passed-in array into the mLetterValues 
		// Since the methods are explicitly written for scrabble, 
		// you can assume that this is an array of 26 elements

		for (int i = 0; i < 26; i++)
		{
			mLetterValues[i] = _letterValues[i];
		}
	}

	int GetLetterValue(char _letter) const 
	{
		// Returns the value of a particular letter
		// The parameter received will always be an upper-case letter
		// Will need to offset this into the array element range 
		// and return that value from the array

		size_t index = static_cast<size_t> (_letter - 'A');

		return mLetterValues[index];
	}

	int GetWordValue(const std::string& _word) const 
	{
		// Returns the total value for a word
		// Use a previous method to help calculate this

		int count = 0;

		for (char letter : _word) 
		{
			count += GetLetterValue(letter);
		}
		return count;
	}

	std::pair<std::string, int> CreatePair(const std::string& _word) const 
	{
		// Creates and returns an std::pair with the word as the key 
		// and the total for that word as the value

		int Value = GetWordValue(_word);
		auto newPair = std::make_pair(_word, Value);
	
		return newPair;
	}

	void LoadWords(const char* _filename) 
	{
		// Open the file located at the filename in read mode.
		std::ifstream file(_filename);

		std::string word;
		std::vector<std::string> temp;

		// Read each word from the file and store it in the vector 'temp'
		while (std::getline(file, word)) 
		{
			temp.push_back(word);
		}

		// Add each pair to the unordered_map data member
		for (const auto& word : temp)
		{
			mScrabbleMap.insert(CreatePair(word));
		}

		file.close();
	}

	int FindValueInMap(const std::string& _word) 
	{
		// Finds a word in the map and returns the value associated with it
		auto pair = mScrabbleMap.find(_word);
		if (mScrabbleMap.contains(_word)) 
		{
			
			int value = mScrabbleMap[_word];
			return value;
		}
		else
		{
			return -1;
		}

	}
};
