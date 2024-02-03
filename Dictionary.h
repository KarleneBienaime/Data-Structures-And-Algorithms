/*
File:			DList.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A hash-mapped data structure using key/value pairs and separate chaining
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
#define LAB_5	1

// Individual unit test toggles
#define LAB5_PAIR_CTOR				1
#define LAB5_CTOR					1
#define LAB5_DTOR					1
#define LAB5_CLEAR					1
#define LAB5_INSERT_NEW				1
#define LAB5_INSERT_EXISTING		1
#define LAB5_FIND					1
#define LAB5_FIND_NOT_FOUND			1
#define LAB5_REMOVE					1
#define LAB5_REMOVE_NOT_FOUND		1
#define LAB5_ASSIGNMENT_OP			1
#define LAB5_COPY_CTOR				1

/************/
/* Includes */
/************/
#include <list>

template<typename Key, typename Value>
class Dictionary 
{

	friend class UnitTests_Lab5;	// Giving access to test code

	struct Pair 
	{
		Key key;			
		Value value;		

		Pair(const Key& _key, const Value& _value) 
		{
			key = _key;
			value = _value;

		}

		// For testing
		bool operator==(const Pair& _comp) const 
		{
			return (_comp.key == key &&
				_comp.value == value);
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	std::list<Pair>* mTable = reinterpret_cast<std::list<Pair>*>(-1);							// A dynamic array of lists (these are the buckets)
	size_t mNumBuckets = -1;																	// Number of elements in mTable
	unsigned int(*mHashFunc)(const Key&) = reinterpret_cast<unsigned int(*)(const Key&)>(-1);	// Pointer to the hash function


public:

	Dictionary(size_t _numBuckets, unsigned int (*_hashFunc)(const Key&)) 
	{
		mNumBuckets = _numBuckets;
		mHashFunc = _hashFunc;
		mTable = new std::list<Pair>[_numBuckets];
	}

	~Dictionary()
	{
		delete[] mTable;
	}

	Dictionary(const Dictionary& _copy) 
	{
		mNumBuckets = _copy.mNumBuckets;
		mHashFunc = _copy.mHashFunc;
		mTable = new std::list<Pair>[mNumBuckets];

		for (int i = 0; i < mNumBuckets; i++) 
		{
			mTable[i] = _copy.mTable[i];
		}
	}

	Dictionary& operator=(const Dictionary& _assign) 
	{
		if (this == &_assign) { return *this; }

		mNumBuckets = _assign.mNumBuckets;	
		mHashFunc = _assign.mHashFunc;	

		delete[] mTable;

		mTable = new std::list<Pair>[mNumBuckets];
		for (int i = 0; i < mNumBuckets; i++)
		{
			mTable[i] = _assign.mTable[i];
		}

		return *this;
	}

	void Clear() 
	{
		for (int i = 0; i < mNumBuckets; i++) 
		{
				mTable[i].clear();
		}
	}

	void Insert(const Key& _key, const Value& _value) 
	{
		int Bucketindex = mHashFunc(_key);
		auto& section = mTable[Bucketindex];


		auto start = section.begin();
		auto end = section.end();

		for (auto it = start; it != end; it++)
		{
			if (it->key == _key)
			{
				it->value = _value;
				return;
			}
		}
		section.push_back(Pair(_key,_value));
	}

	const Value* Find(const Key& _key) 
	{
		int Bucketindex = mHashFunc(_key);
		auto& section = mTable[Bucketindex];

		auto start = section.begin();
		auto end = section.end();

		for (auto it = start; it != end; it++)
		{
			if (it->key == _key) // found
			{
				
				return &it->value;
			}
		}

		return nullptr;
	}

	bool Remove(const Key& _key) 
	{
		int Bcode = mHashFunc(_key);
		auto start = mTable[Bcode].begin();
		auto end = mTable[Bcode].end();

		for (auto i = start; i != end; i++)
		{
			if (i->key == _key)
			{
				mTable[Bcode].erase(i);
				return true;
			}
		}
		
		return false;
	}
}; 