#include "HashFunction.h"
#include <iostream>

using namespace std;

namespace HashFunction {

	// MAKE NEW FUNCTIONS
	// Constructor
	HashTable::HashTable() {
		std::cout << "HASH TABLE DEBUG: A new hash table (an array of lists of pairs) has been created, size [" << hashTableSize << "] lists.\n" << std::endl;
	};

	// Destructor
	HashTable::~HashTable() {
		// Iterate through the hash table array, and...
		for (int i = 0; i < GetHashTableSize(); i++) {			
			for (auto pairIterator = begin(HashTableElements[i]); pairIterator != end(HashTableElements[i]); pairIterator++) {
				delete &pairIterator->second;
			}
		}
	};

	// Hash function of return type int (the key, aka the hashed value).
	unsigned int HashTable::ImprovedHash(PersonnelRecord entry) {
		// 1: Make sure the contents of the struct can be summed together
		unsigned int tempName = ConvertToNumber(entry.name);
		unsigned int tempAge = entry.age;
		unsigned int tempSalary = entry.salary;
		
		// 2: Hash the value into a key
		unsigned int key = tempSalary / tempName / tempAge;

		// Make sure the key's number does not exceed the size of the table available
		while (key > GetHashTableSize()) {
			key -=10;
		}

		// 3: Return the key
		return key;
	};

	const bool HashTable::IsEmpty() const {
		// Create a counter for the number of elements found in the hash table
		int sum = 0;

		// Iterate through the hash table, and...
		for (int i = 0; i < hashTableSize; i++) {
			// For every element found, add its size (1 element) to the counter
			sum += HashTableElements[i].size();
		}

		// If 0 elements were found, return that the list is empty
		if (sum == 0) {
			return true;
		}

		// ... else return that the list is not empty
		return false;
	};

	const bool HashTable::HashKeyExists(int key) {
		// Assume by default that the key will not be found
		bool doesKeyExist = false;

		// Why would I create a new int here rather than using the passed-in value?
		int hashedValue = key;

		// Create a new element object which is a copy of the memory address of the passed-in key.
		list<pair<int, DoubleLinkedList<PersonnelRecord>>>& element = HashTableElements[hashedValue];
		
		// For every element found in the hash table...
		for (
			auto hashIterator = begin(element);
			hashIterator != end(element);
			hashIterator++)

			// Set its existence to true
			doesKeyExist = true;

		// Return true or false whether the parameter key exists
		return doesKeyExist;
	};

	// A function to add a new element to the hash table by its values
	void HashTable::AddNewRecord(const char* name, int age, int salary) {
		std::cout << "HASH TABLE DEBUG:\tA new record is attempting to be added to the hash table:" << std::endl;

		// 1: Create a pointer to a new record to accept the parameters passed in 
		PersonnelRecord* newRecord = new PersonnelRecord;
		newRecord->name = name;
		newRecord->age = age;
		newRecord->salary = salary;

			// Print the parameters accepted to the console
			std::cout
				<< "HASH TABLE DEBUG:\tName (" << newRecord->name
				<< "), age (" << newRecord->age
				<< "), salary (" << newRecord->salary << ")."
				<< std::endl;
		
		// 2: Pass the dereferenced record object through the hash function to create and return a key
		int key = ImprovedHash(*newRecord);

		// 3: Create a reference to a list object, called 'tempList', at the position in the array where such a list would be placed if a legitimate key exists at that location.
		list<pair<int, DoubleLinkedList<PersonnelRecord>>> & tempList = HashTableElements[key];
		std::cout << "HASH TABLE DEBUG:\tThe list at hash table key [" << key << "] was accessed." << std::endl;
		
		// 4: If the key that arises from the has function already has a list, check whether this record already exists within
		// *** --- *** MUST CHECK FOR EXISTENCE BEFORE NON-EXISTENCE BECAUSE NON-EXISTENCE CREATES NEW ENTRY!! *** --- ***
		if (HashKeyExists(key)) {
			std::cout << "HASH TABLE DEBUG:\tHash table key [" << key << "] already contains a list." << std::endl;
			// If the key already exists, then there is one pair inside the list <int, double linked list>. use the double linked list to find whether this record exists inside.
			// 1: Random-access the array at the location of this KEY.
			// 2: Go to the beginning of the LIST at this KEY (the first PAIR).
			// 3: Go to the second object of the PAIR (the double linked list).
			// 4: Search the double linked list for whether the record already exists 


			// If the key does exist, create an iterator which will traverse the list's pairs (there should only ever be one), but just in case...
			for (auto pairIterator = begin(tempList); pairIterator != end(tempList); pairIterator++) {
				// 4.1: If the pairs are identical the record already exists - NO ACTION.
				// Search the double linked list for a record that exactly matches the one to be added, and if we can find the new record in the list...
				if (pairIterator->second.find(*newRecord) == true) {
					std::cout << "HASH TABLE DEBUG:\tThis is a duplicate entry - This record already exists so has not been added to the hash table.\n" << std::endl;
					break;
				};
				
				// else...
				// 4.2: If the pairs are not identical then the record does not exist yet - create a new entry by adding the new record to the second item of the list's pair (the double linked list)
				pairIterator->second.pushBack(*newRecord);
				std::cout << "HASH TABLE DEBUG:\tThis is not a duplicate entry - New entry added as below:" << std::endl;

				// Print the parameters accepted to the console
				std::cout
					<< "HASH TABLE DEBUG:\tName (" << newRecord->name
					<< "), age (" << newRecord->age
					<< "), salary (" << newRecord->salary << ").\n"
					<< std::endl;
			};
		};

		// 5: If the key that arises from the has function does not yet have a list...
		if (!HashKeyExists(key)) {
			// If the key does not 'exist' (does not already have a list in it) then the list at this address does not have a paired integer with a double linked list. 
			std::cout << "HASH TABLE DEBUG:\t\tHash table key [" << key << "] did not yet contain a list. New list created." << std::endl;
			// 5.1: Create a new double linked list for this address
			DoubleLinkedList<PersonnelRecord>* newDLL = new DoubleLinkedList<PersonnelRecord>;
			// 5.2: Add the new entry to the double linked list
			newDLL->addToEmpty(*newRecord);
			// 5.3: Emplace the new pair in the new list with this hash key's position in the array, and assign the pair their objects (key number, new double linked list object)
			tempList.emplace_back(key, *newDLL);

			std::cout
				<< "HASH TABLE DEBUG:\t\t\t\tNew element added to key [" << key
				<< "] with name (" << HashTableElements[key].begin()->second.begin()->data.name
				<< "), age (" << HashTableElements[key].begin()->second.begin()->data.age
				<< "), salary (" << HashTableElements[key].begin()->second.begin()->data.salary << ").\n"
				<< std::endl;
		};
		
		delete newRecord;
		newRecord = nullptr;

		
	};
	
	void HashTable::RemoveRecord(const char* name, int age, int salary) {
		// 0: Create a temporary struct for the particulars of the record targeted for deletion
		PersonnelRecord target;
		target.name = name;
		target.age = age;
		target.salary = salary;

		// 1: Create an unsigned int to work with the key temporarily
		unsigned int hashedValue = ImprovedHash(target);

		// Print the parameters accepted to the console
		std::cout
			<< "HASH TABLE DEBUG:\tA request to delete a record has been made: name (" << target.name
			<< "), age (" << target.age
			<< "), salary (" << target.salary 
			<< "), key ["<< hashedValue << "]."
			<< std::endl;

		// *** --- *** MUST CHECK FOR EXISTENCE BEFORE NON-EXISTENCE BECAUSE NON-EXISTENCE CREATES NEW ENTRY!! *** --- ***
		// 2: Check if the key exists
		if (HashKeyExists(hashedValue)) {
			// 2.1: Create an object reference to the target list, so I can look at the pair within the hash table at the location of the passed-in key
			auto& targetList = HashTableElements[hashedValue];

			// 2.2: Create a reference to the pair for the target list
			auto pairIterator = begin(targetList);

			if (pairIterator->second.find(target) == true) {
				std::cout << "HASH TABLE DEBUG:\tThe record for deletion exists in this key." << std::endl;
				std::cout << "HASH TABLE DEBUG:\tThe record was found in position [" << pairIterator->second.position(target) << "].\n" << std::endl;
				// Delete the node with this record by its position number
			};
		}

		// 3: Check if the key is non-existent
		if (!HashKeyExists(hashedValue)) {
			// 3.1: Follow up on non-existence process from hashing algorithm
			std::cout << "HASH TABLE DEBUG:\tHash key [" << hashedValue << "] has no records - no deletion actioned.\n" << std::endl;
		};
	};

	void HashTable::RemoveItem(unsigned int key) {
		std::cout << "HASH TABLE DEBUG:\tA request to delete a key has been made." << std::endl;
		// 1: Create an int to work with the key temporarily
		unsigned int hashedValue = key;

		// 2a: Check if the key is non-existent
		if (!HashKeyExists(hashedValue)) {
			// Follow up on non-existence process from hashing algorithm
			std::cout << "HASH TABLE DEBUG:\tHash key ["<< key <<"] was not found for deletion." << std::endl;
		}

		// 2b: Check if the key exists
		if (HashKeyExists(hashedValue)) {
			std::cout << "HASH TABLE DEBUG:\tHash key [" << key << "] was found for deletion." << std::endl;
			// 3: Create an object reference to the target list, so I can look at the pair within the hash table at the location of the passed-in key
			auto& targetList = HashTableElements[hashedValue];
			
			// Create a reference to the pair for the target list
			auto pairIterator = begin(targetList);

			// Wipe the double linked list at the target pair
			targetList.begin()->second.clear();
			targetList.begin()->second.count();
			targetList.begin()->second.isEmpty();
			std::cout << "HASH TABLE DEBUG:\tThe double linked list of key [" << key << "] has been cleared.\n" << std::endl;
		};
	};

	const int HashTable::GetHashTableSize() {
		return hashTableSize;
	};

	void HashTable::PrintHashTable() {
		std::cout << "\n|||	***	---	COMMENCING PRINTING OF ALL KEYS CONTAINING HASHED VALUES --- *** |||" << std::endl;
		// Iterate through the hash table, and...
		for (int i = 0; i < GetHashTableSize(); i++) {
			// If the element being iterated over is empty, continue to the next one, otherwise...
			if (HashTableElements[i].size() == 0) continue;

			// For every pair in this element (list) [there should only ever be one]...
			for (
				auto pairIterator = HashTableElements[i].begin();
				pairIterator != HashTableElements[i].end();
				pairIterator++) {

				std::cout
					<< "Index (" << i << ") " << std::endl;
					pairIterator->second.print(i);
			};
		};
		std::cout << "||| *** --- HASHTABLE PRINTOUT COMPLETE --- *** |||\n" << std::endl;
	};

	unsigned int HashTable::ConvertToNumber(const char* string) {
		// Find the size of the string array
		size_t size = sizeof(string) / sizeof(string)[0];
		// Create a temporary variable for counting the ASCII value of the string passed-in as a parameter
		unsigned int alphanumericValue = 0;
		// Create a temporary variable for working with an individual character
		char temp;

		// Then, for the whole string...
		for (size_t i = 0; i < size; i++) {
			// If a character is uppercase...
			if (isupper(string[i])) {
				// Convert it to lowercase before adding its ASCII value
				temp = string[i];
				alphanumericValue += (tolower(temp));
				continue;
			}

			alphanumericValue += (string[i]);
		}

		// Return the summed ASCII values of all elements in the array of characters
		return alphanumericValue;
	};
}