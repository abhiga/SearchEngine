
// Implementation of a dictionary using an array and binary search
// It will inherit from the ArrayDictionary

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bsearch-dictionary.h"

// Constructor
BinarySearchDictionary::BinarySearchDictionary()
{
	sorted = false;
}

bool
BinarySearchDictionary::addRecord( KeyType key, DataType record) {
	sorted = false;
	return ArrayDictionary::addRecord(key, record);
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
BinarySearchDictionary::findRecord( KeyType key)
{
	printf("B\n",sorted);
	if (!sorted) {
		sort();
		sorted = true;
	}
	//printf("%d\n",1234567);
	// Use binary search
	printf("B\n",sorted);

	// Add your implementation here
	int low = 0;
	int high = currentNumber - 1;
	while (high >= low){
		int mid = (high + low) / 2;
		int result = strcmp(key, array[mid].key);
		if (result == 0){
			//printf("%d\n",array[mid].data);
			return array[mid].data;
		}
		else if (result < 0){
			high = mid - 1;
		}
		else{
			low = mid + 1;
		}
	}
	return NULL;
}


// Sort array using heap sort
void
BinarySearchDictionary::sort()
{
	//printf("Before\n");
	//for (int i = 0; i < currentNumber; i++) {
	//	printf("%s\n", array[i].key);
	//}

        // Add your code here

	//printf("After\n");
	//for (int i = 0; i < currentNumber; i++) {
	//	printf("%s\n", array[i].key);
	//}
	ArrayDictionaryNode temp;
	for (int i = 0; i < currentNumber; i++ ) {
		for (int j = 0; j < currentNumber - 1; j++ ) {
			if (strcmp(array[j].key, array[j+1].key) < 0) {
				temp.key = array[j].key;
				array[j].key = array[j+1].key;
				array[j+1].key = temp.key;
				temp.data = array[j].data;
				array[j].data = array[j+1].data;
				array[j+1].data = temp.data;
			}
		}
	}
}




