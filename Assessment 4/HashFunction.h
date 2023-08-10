#pragma once
#include <functional>
#include <list>
#include <string>
#include "DoubleLinkedList.h"
#include "PersonnelFile.h"

namespace HashFunction
{	
	// Consider creating the hash table as a template so that I can change the object stored inside that I want to save/return
	class HashTable {
		

	private:
		/* Variable for the size of the hash table.
		Static because we aren't going to reference an instance of the variable.
		Const because the variable is initialised within the class definition.*/
		const static int hashTableSize = 100;

		// Create the hash table as an array of lists of pairs, being an integer (the hash key) paired with a double linked list of structs. The double linked list will acommodate separate chain hashing. The PersonnelRecord struct is the value/object stored within each node, so that one hash table address may store multiple records which have the same hash key.
		std::list<std::pair<int, DoubleLinkedList<PersonnelRecord>>> HashTableElements[hashTableSize];

	public:
		HashTable();
		~HashTable();

		// ADD MY FUNCTIONS HERE
		// Adjusted hash function
		unsigned int ImprovedHash(PersonnelRecord entry);
		
		// A function to determine whether or not the hash table is empty
		const bool IsEmpty() const;

		// A bool function which returns whether or not a passed-in hash key can be found in the hash table.
		const bool HashKeyExists(int key);

		// A function to add a new element to the hash table by its values
		void AddNewRecord(const char* name, int age, int salary);

		// A function to remove an element from the hash table by its values
		void RemoveRecord(const char* name, int age, int salary);

		// A function to remove all elements from the hash table by key number
		void RemoveItem(unsigned int key);

		// A function to print the contents of the hash table, both key and value, to the console
		void PrintHashTable();

		// A public function to return the volume of objects inside the hash table (private member variable)
		const int GetHashTableSize();

		unsigned int ConvertToNumber(const char* string);
	};
};

