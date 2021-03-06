
// Implementation of a dictionary using an array and sequential search
// The array will be dynamically resized if necessary

#include <stdlib.h>
#include <string.h>

#include "array-dictionary.h"

// Constructor
ArrayDictionary::ArrayDictionary()
{
  // Add your code here
	maxNumber = 100;
	currentNumber = 0;
	array = new ArrayDictionaryNode[maxNumber];	
}

// Add a record to the dictionary. Returns false if key already exists
bool
ArrayDictionary::addRecord( KeyType key, DataType record)
{
        // Add your code here
	for (int i = 0; i < currentNumber; i++) {
		if (!strcmp(array[i].key, key)) {
			array[i].data = record;
			return false;
		}
	}
	if (currentNumber == maxNumber) {
		int oldSize = maxNumber;
		maxNumber = maxNumber * 2;
		ArrayDictionaryNode *newArray = new ArrayDictionaryNode[maxNumber];
		for (int i = 0; i < oldSize; i++) {
			newArray[i].key = strdup(array[i].key);//new char[50];
			//strcpy(newArray[i].key, array[i].key);
			newArray[i].data = new DataType;
			newArray[i].data = array[i].data;
		}
		delete []array;
		array = newArray;
	}
	array[currentNumber].key = strdup(key);
	//strcpy(array[currentNumber].key, key);
	array[currentNumber].data = new DataType;
	array[currentNumber].data = record;
	currentNumber++;
	return true;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
ArrayDictionary::findRecord(KeyType key)
{
        // add your code here
	for (int i = 0; i < currentNumber; i++) {
		if (!strcmp(array[i].key, key)) 
			return array[i].data;
	}

	return NULL;
}

// Removes one element from the table
bool
ArrayDictionary::removeElement(KeyType key)
{
        // Add your code here
	int count;
	int flag = 0;
	for (int i = 0; i < currentNumber; i++) {
		if (!strcmp(array[i].key, key)) {
			flag = 1;
			count = i;
			break;
		}
	}
	if (flag == 1) {

	
		int newi = 0;    
    	ArrayDictionaryNode *newArray = new ArrayDictionaryNode[maxNumber];
    	for (int i = 0; i < currentNumber; i++){
			if(count!=i) { 
	    		newArray[newi].key = strdup(array[i].key);
	    		newArray[newi].data = new DataType;
	    		newArray[newi].data = array[i].data;
				newi++;
			}
			
		}
		currentNumber--;
		delete [] array;
		array = newArray;
    	return true;
	}
	return false;	
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
ArrayDictionary::keys(int * n)
{
        // Add yoru code here
	KeyType* rkeys = new KeyType[currentNumber];
	for (int i = 0; i < currentNumber; i++)
		rkeys[i] = array[i].key;
	*n = currentNumber;
	return rkeys;
}
