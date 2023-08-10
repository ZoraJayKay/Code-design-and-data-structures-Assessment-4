#pragma once
#include <iostream>
#include "Node.h"
#include <assert.h>

// Create a template that will accept a type of object, 'D'
template<typename D>
class DoubleLinkedList
{
protected:
	// Node navigation pointers (initialised in the Constructor)
	Node<D>* Head;
	Node<D>* Tail;

public:
	// Default constructor
	DoubleLinkedList() {
		Head = nullptr;
		Tail = nullptr;

		// OPTIONAL DEBUG CONSOLE PRINTOUT
		std::cout << "DOUBLE LINK LIST DEBUG:\tNew double link list created." << std::endl;
	};

	// Destructor
	~DoubleLinkedList() {
#ifndef NDEBUG
		std::cout << "\nDOUBLE LINK LIST DEBUG:\t\tDouble link list destruction started." << std::endl;
#endif
		// Delete all remaining nodes
		clear();

		// Delete all node navigation pointers
		delete Head;
		Head = nullptr;

		delete Tail;
		Tail = nullptr;
#ifndef NDEBUG
		std::cout << "DOUBLE LINK LIST DEBUG:\t\tDouble link list has been destroyed.\n" << std::endl;
#endif
	};

	// *** Node navigation functions ***
	// Add a new value if the linked list is empty
	void addToEmpty(D value) {
		// If the linked list doesn't have a 'Head' pointer yet (if the linked list is empty)...
		if (Head == NULL) {
			// Create a pointer to a new node
			Node <D>* newTemp = new Node<D>;
			// Populate the new node with the passed-in value but do not point its 'next' pointer to any address
			newTemp->data = value;
			newTemp->nextNode = NULL;
			newTemp->previousNode = NULL;

			// Then the new node is the only node in the list, so make the new node both the linked list's Head and Tail
			Head = newTemp;
			Tail = newTemp;

			// OPTIONAL DEBUG CONSOLE PRINTOUT
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tList was empty: New node added to the front of the list." << std::endl;
			return;
		}

		// If the linked list DOES have a 'Head' pointer already, insert this in front of it.
		else if (Head != NULL) {
			pushFront(value);
		}
	};

	// Add a new value to the front of the list
	void pushFront(D value) {
		// If the linked list doesn't have a 'Head' pointer yet (if the linked list is empty)...
		if (Head == NULL) {
			// Add the first entry to the linked list
			addToEmpty(value);
			// Do not continue the rest of the function
			return;
		}

		else if (Head != NULL) {
			// If the linked list DOES have a 'Head' pointer already...
			// Create a pointer to a new node
			Node<D>* newtemp = new Node<D>;
			// Populate the new node with the passed-in value 
			newtemp->data = value;
			// Make the 'previous' pointer of the new node point nowhere
			newtemp->previousNode = NULL;
			// The current head will be second, so make the current head's 'previous' pointer equal to the new node
			Head->previousNode = newtemp;
			// Make the 'next' pointer of the new node point to the current 'Head' pointer (the first entry) of the linked list
			newtemp->nextNode = Head;
			// Replace the address of the 'Head' of the linked list with the address of the new node, thereby making the old 'Head' entry #2
			//Head = temp;
			Head = Head->previousNode;
		}
	};

	// Add a new value to the end of the list
	void pushBack(D value) {
		// If the linked list doesn't have a 'Tail' pointer yet (if the linked list is empty)...
		if (Tail == NULL) {
			// Add the first entry to the linked list
			addToEmpty(value);
			// Do not continue the rest of the function
			return;
		}

		else if (Tail != NULL) {
			// If the linked list DOES have a 'Tail' pointer already...
			// Create a pointer to a new node
			Node<D>* newTemp = new Node<D>;
			// Populate the new node with the passed-in value 
			newTemp->data = value;
			// Make the current 'Tail' pointer (the last entry) of the linked list point to the address of the new node
			Tail->nextNode = newTemp;
			// Make the 'previous' pointer of the new 'Tail; point to the old 'Tail'
			newTemp->previousNode = Tail;
			// Replace the address of the current 'Tail' with the address of the new node, thereby making the old 'Tail' the 2nd last
			Tail = Tail->nextNode;
			// Make the 'Tail' point nowhere
			Tail->nextNode = NULL;

			// OPTIONAL DEBUG CONSOLE PRINTOUT
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tNew node added to the back of the list." << std::endl;
		}
	};

	// Add a new value one-past the specified iterator location
	void insert(D nodeData, int iteratorNumber) {
		// Create a counter for determining when the iterator has been reached (starts at 1 because the list doesn't use 0-indexing)
		int counter = 1;


		// If the linked list doesn't have a 'Head' pointer yet (if the linked list is empty)...
		if (Head == NULL) {
			// Add the new node to the end of the linked list
			addToEmpty(nodeData);
			// Do not continue the rest of the function
			return;
		}

		else if (Head != NULL) {
			// Set the iterator for the linked list, starting at the 'Head' (the beginning)...
			Node <D>* newIterator = begin();

			// ... and until the iterator reaches the end of the linked list...
			while (newIterator != NULL) {
				// ... check if the target insertion point has been found...
				if (counter == iteratorNumber) {
					// ... and if the target insertion node is the last node in the linked list...
					if (newIterator->nextNode == NULL) {
						pushBack(nodeData);
						return;
					}

					// ... or if the target insertion point was found but BEFORE reaching the 'Tail'...
					else {
						// Set the temp pointer to a new node
						Node <D>* newTemp = new Node<D>;
						// Populate the new node with the passed-in value 
						newTemp->data = nodeData;
						// Assign the new node the 'next' pointer that would have been iterated through
						newTemp->nextNode = newIterator->nextNode;
						newTemp->previousNode = newIterator;
						newIterator->nextNode->previousNode = newTemp;
						newIterator->nextNode = newTemp;
					}

					// After the target insertion point is found and the new node has been inserted, set the address of the iterator equal to the node just inserted and end the loop.
					//newIterator->nextNode = newTemp;

					// OPTIONAL DEBUG CONSOLE PRINTOUT
					std::cout << "DOUBLE LINK LIST DEBUG:\t\tElement with contents (" << nodeData << ") was added to the linked list after element " << iteratorNumber << "." << std::endl;
					return;
				}

				// ... and if the target insertion point has not yet been found, set the address of the iterator equal to the next node to be iterated through.
				newIterator = newIterator->nextNode;
				counter++;
			}

			// ... otherwise the element was not found.
			// OPTIONAL DEBUG CONSOLE PRINTOUT
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tElement with contents (" << nodeData << ") was not found in the linked list." << std::endl;
		}
	};

	// Search the list for a given piece of data
	const bool find(D searchValue) {
		// Start the iterator at the 'Head'
		Node<D>* newIterator = begin();

		// Track the current index
		int counter = 0;
		// Track the search
		bool foundCounter = false;

		if (newIterator != NULL) {
			while (newIterator != Tail) {
				counter++;
				if (newIterator->data == searchValue) {
					foundCounter = true;
					break;
				}

				else {
					newIterator = newIterator->nextNode;
				}
			}

			if (foundCounter == true) {
				std::cout << "DOUBLE LINK LIST DEBUG:\t\tRecord was found in node " << counter << " of the list." << std::endl;
				return foundCounter;	// true
			}

			else {
				std::cout << "DOUBLE LINK LIST DEBUG:\t\tSearched " << counter << " elements. Record was not found in the list." << std::endl;
				return foundCounter;	// false
			}
		}

		else {
			// if the node is null to begin with, then the list is empty
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe list was empty - nothing to search." << std::endl;
			return foundCounter;	// false
		}
	}

	// Search the list for a given piece of data and return its position as an integer
	const int position(D searchValue) {
		// Start the iterator at the 'Head'
		Node<D>* newIterator = begin();

		// Track the current index
		int counter = 0;
		// Track the search
		bool foundCounter = false;

		if (newIterator == NULL) {
			// if the node is null to begin with, then the list is empty
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe list was empty - nothing to search." << std::endl;
			return 0;
		}

		else if (newIterator != NULL) {
			while (newIterator != NULL) {
				counter++;
				if (newIterator->data == searchValue) {
					foundCounter = true;
					break;
				}
				newIterator = newIterator->nextNode;
			}

			if (foundCounter == true) {
				std::cout << "DOUBLE LINK LIST DEBUG:\t\tRecord was found in node " << counter << " of the list." << std::endl;
				return counter;
			}

			else {
				std::cout << "DOUBLE LINK LIST DEBUG:\t\tRecord was not found in the list. Searched " << counter << " elements." << std::endl;
				return 0;
			}
		}		
	}

	// Return an iterator to the first element
	Node<D>* begin() {
		// Create an iterator for the linked list, starting at the 'Head' (the beginning)...
		return Head;
	};

	// Return an iterator to a null element
	Node<D>* end() {
		// Create an iterator for the linked list, starting at the 'Tail' (the end)...
		return Tail->nextNode;
	};

	// Return the first element by value, assert if no elements
	D first() {
		// Before beginning, assert that the list is not empty
		assert(Head != NULL && Tail != NULL);
		// Create an iterator for the linked list, starting at the 'Head' (the beginning)...
		Node<D>* newIterator = begin();

		// OPTIONAL DEBUG CONSOLE PRINTOUT
		std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe data in the first element is: (" << newIterator->data << ")." << std::endl;

		// Return the first element's recorded value
		return newIterator->data;
	};

	// Return the last element by value, assert if no elements
	D last() {
		// Before beginning, assert that the list is not empty
		assert(Head != NULL && Tail != NULL);
		// Create an iterator for the linked list, starting at the 'Tail' (the end)...
		Node<D>* newIterator = Tail;

		// OPTIONAL DEBUG CONSOLE PRINTOUT
		std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe data in the last element is: (" << newIterator->data << ")." << std::endl;

		// Return the last element's recorded value
		return newIterator->data;
	};

	// Return how many elements exist in the list
	const int count() {
		int counter = 0;
		// If the 'Head' is empty (if the 'Head' returns a null pointer)...
		if (begin() == NULL) {
			// OPTIONAL DEBUG CONSOLE PRINTOUT
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tA count was performed: The count returned 0 elements." << std::endl;
			// Return that the count is zero elements.
			return 0;
		}

		Node<D>* newIterator = begin();
		// If the linked list DOES have a non-NULL 'Head' pointer...
			// ... then until the iterator reaches the end of the linked list...
			while (newIterator != NULL) {
				newIterator = newIterator->nextNode;
				counter++;
			}
			// OPTIONAL DEBUG CONSOLE PRINTOUT
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tA count was performed: The list has " << counter << " elements." << std::endl;
			// return the count of how many elements were found in the linked list
			return counter;
	};

	// Remove an element by its element number as a passed-in position within the list
	void erase(int elementForDeletion) {
		Node<D>* newTemp;
		Node<D>* newIterator;

		// If the list is empty...
		if (isEmpty() == true) {
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe list was empty - nothing to search." << std::endl;
			// ... exit the function.
			return;
		};

		// otherwise...
		int counter = 1;	// Because a list is not a 0-indexed container
		int totalSize = count();

		// If the element number (the position in the list) of the 'Head' is the same as the element number for deletion...
		if (elementForDeletion == counter) {
			// ... delete the 'Head'.
			popFront();
			// ... exit the function.
			return;
		};

		// If the element number (the position in the list) of the 'Tail' is the same as the element number for deletion...
		if (elementForDeletion == totalSize) {
			// ... delete the 'Tail'.
			popBack();
			// ... exit the function.
			return;
		};

		// ... Otherwise, starting at the 'Head'...
		newIterator = begin();
		while (counter < totalSize) {
			// If the element number (the position in the list) of the iterated node is the same as the element number for deletion...
			if (counter == elementForDeletion) {
				// Copy the memory address of the target node...
				newTemp = newIterator->nextNode;
				// Skip the node for deletion in the list sequence...
				newIterator->nextNode = newIterator->nextNode->nextNode;
				// ... nullify the contents of the memory address of the target node
				delete newTemp;
				newTemp = nullptr;
				// ... exit the function.
				return;
			}

			// ... If the target node for deletion hasn't been found yet...
			else {
				// ... look at the next node
				newIterator = newIterator->nextNode;
				counter++;
			};
		};
	};

	// Remove an element by its object
	void erase(Node<D>& nodeForDeletion) {
		Node<D>* newTemp;
		Node<D>* newIterator;

		// In this context an element is a node and its iterator is a pointer to its memory address.
		// So we need to remove a Node object according to a passed-in memory address (a pointer)

		// If the list is empty...
		if (isEmpty() == true) {
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe list was empty - nothing to erase." << std::endl;

			// ... exit the function.
			return;
		};

		// If the memory address of the 'Head' is the same as the memory address of the element for deletion...
		if (Head == &nodeForDeletion) {
			// ... delete the 'Head'.
			popFront();
			// ... exit the function.
			return;
		};

		// If the memory address of the 'Tail' is the same as the memory address of the element for deletion...
		if (Tail == &nodeForDeletion) {
			// ... delete the 'Tail'.
			popBack();
			// ... exit the function.
			return;
		};

		// ... Otherwise, starting at the 'Head'...
		newIterator = begin();
		while (newIterator != NULL) {
			// ... if the memory address of the next node is the same as the memory address of the element for deletion...
			if (newIterator->nextNode == &nodeForDeletion) {
				// Copy the memory address of the target node...
				newTemp = newIterator->nextNode;
				// Skip the node for deletion in the list sequence...
				newIterator->nextNode = newIterator->nextNode->nextNode;
				// ... nullify the contents of the memory address of the target node
				delete newTemp;
				newTemp = nullptr;
				// ... exit the function.
				return;
			}

			// ... If the target node for deletion hasn't been found yet...
			else {
				// ... look at the next node
				newIterator = newIterator->nextNode;
			};
		};
	};

	// Remove all elements with matching value
	void remove(D nodeDataForDeletion) {
		Node<D>* newIterator;

		// In this context an element is a node and its value is its data.
		int counter = 0;

		// First, if the list is empty...
		if (isEmpty() == true) {
			// OPTIONAL DEBUG CONSOLE PRINTOUT
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe list was empty so no elements were removed." << std::endl;

			// ... exit the function.
			return;
		};

		// Otherwise, for as long as the data of the 'Head' is the same as the data for deletion...
		while (Head->data == nodeDataForDeletion) {
			// ... delete the 'Head' and continue the function.
			popFront();
			counter++;
		};

		// ... Then, if the data of the 'Tail' is the same as the data for deletion...
		while (Tail->data == nodeDataForDeletion) {
			// ... delete the 'Tail' and continue the function.
			popBack();
			counter++;
		};

		newIterator = begin();
		// ... Then, iterate through the remaining elements until reaching the 'Tail'...
		while (newIterator != NULL) {
			// ... if we reach the 'tail'...
			if (newIterator->nextNode == NULL) {
				// OPTIONAL DEBUG CONSOLE PRINTOUT
				std::cout << "DOUBLE LINK LIST DEBUG:\t\t " << counter << " elements of value (" << nodeDataForDeletion << ") were removed." << std::endl;

				// End the loop
				return;
			};

			// ... but before reaching the 'Tail', if the data of the next node is the same as the data for deletion...
			if (newIterator->nextNode->data == nodeDataForDeletion) {
				// Copy the memory address of the node to be deleted...
				Node<D>* newTemp = newIterator->nextNode;
				// Skip the node for deletion in the list sequence (node after deletion)...
				newTemp->nextNode->previousNode = newIterator;
				// Skip the node for deletion in the list sequence (node before deletion)...
				newIterator->nextNode = newIterator->nextNode->nextNode;
				// ... nullify the contents of the memory address of the target node and continue the function.
				delete newTemp;
				newTemp = nullptr;
				counter++;
			}

			// ... If a target node for deletion hasn't been found yet...
			else {
				// ... look at the next node.
				newIterator = newIterator->nextNode;
			};
		};
	};

	// Remove the last element
	void popBack() {
		// If the linked list doesn't have a 'Tail' pointer yet (if the linked list is empty)...
		if (Tail == NULL) {
			// There is nothing to delete; do not continue the rest of the function

			return;
		}

		if (Tail->previousNode != NULL) {
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe Tail with data (" << Tail->data << ") will be removed. The new last element has data (" << Tail->previousNode->data << ")." << std::endl;
			Node<D>* newIterator = Tail;
			Tail = Tail->previousNode;
			delete newIterator;
			newIterator = nullptr;
			return;
		}

		if (Tail->previousNode = NULL) {
			Node<D>* newIterator = Tail;
			delete newIterator;
			newIterator = nullptr;
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe first element (" << newIterator->data << ") was removed. This was the final element and the Tail.\n" << std::endl;
			return;
		};
	};

	// Remove the first element
	void popFront() {
		// If the linked list doesn't have a 'Head' pointer yet (if the linked list is empty)...
		if (Head == NULL) {
			// There is nothing to delete; do not continue the rest of the function
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThere were no elements to delete. This function will now end.\n" << std::endl;
			return;
		}

		Node<D>* newIterator = begin();	// iterator = Head

		if (Head->nextNode != NULL) {
			Head = newIterator->nextNode;

			// OPTIONAL DEBUG CONSOLE PRINTOUT
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe first element (" << newIterator->data << ") was removed. The new first element is (" << Head->data << ")." << std::endl;

			// Nullify / clear the memory address of the original 'Head' node.
			delete newIterator;
			newIterator = nullptr;
			return;
		};

		if (Head->nextNode = NULL) {
			delete newIterator;
			newIterator = nullptr;
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe first element (" << newIterator->data << ") was removed. This was the final element and the Head.\n" << std::endl;
			return;
		};
	};

	// Return a Boolean, true if the list is empty, false otherwise
	const bool isEmpty() {
		// If the memory address of the 'Head' pointer is null AND the memory address of the 'Tail' pointer is also null...
		if (Head == NULL && Tail == NULL) {
#ifndef NDEBUG
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe list is empty (all pointers are NULL)." << std::endl;
#endif
			// return that the list is empty
			return true;
		}
		// otherwise return that the list is not empty
#ifndef NDEBUG
		std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe list is not empty (it contains non-NULL pointers)." << std::endl;
#endif
		return false;
	};

	// Remove all elements from the list
	void clear() {
		Node<D>* newIterator;
		newIterator = begin();
		Node<D>* newTemp = newIterator;

		if (isEmpty() == true) {
#ifndef NDEBUG
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe list was already clear." << std::endl;
#endif
			return;
		}

		int counter = 0;

		while (newIterator != nullptr) {
			newTemp = newIterator->nextNode;
			delete newIterator;
			newIterator = nullptr;
			newIterator = newTemp;
			counter++;
		};

		delete newIterator;
		newIterator = nullptr;
		delete newTemp;
		newTemp = nullptr;
		Head = nullptr;
		Tail = nullptr;
#ifndef NDEBUG
		std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe list has been cleared, " << counter << " items were removed.\n" << std::endl;
#endif
	};

	// Print all elements in the double linked list for a given key
	void print(int key) {
#ifndef NDEBUG
		std::cout << "DOUBLE LINK LIST DEBUG:\t\tA print of the double linked list is starting." << std::endl;
#endif
		if (isEmpty() == true) {
#ifndef NDEBUG
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe list had nothing to print." << std::endl;
#endif
			return;
		}

		else {
			Node<D>* newIterator = begin();
			int counter = 1;

			while (newIterator != NULL) {
#ifndef NDEBUG
				std::cout << "DOUBLE LINK LIST DEBUG: \t\tIndex [" << key << "] Node [" << counter << "]: ";
				newIterator->Print();
#endif
				newIterator = newIterator->nextNode;
				counter += 1;
			}
		}
#ifndef NDEBUG
		std::cout << "DOUBLE LINK LIST DEBUG:\t\tPrintout of the double linked list is complete.\n" << std::endl;
#endif
	}

	void sort() {
		Node<D>* newTemp;

#ifndef NDEBUG
		std::cout << "DOUBLE LINK LIST DEBUG:\t\tA sort of the double linked list is starting." << std::endl;
#endif
		if (isEmpty() == true) {
#ifndef NDEBUG
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tThe list had nothing to print." << std::endl;
#endif
			return;
		}

		// Create a trigger for whether or not a swap occurred in a loop
		bool swapped = false;

		int length = count();

		do {
			swapped = false;
#ifndef NDEBUG
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tLooping bool 'Swapped' set to false (" << swapped << ")." << std::endl;

			int counter = 0;

			std::cout << "DOUBLE LINK LIST DEBUG:\t\tLooping node counter reset." << std::endl;
#endif
			// Set the iterator for the linked list, starting at the 'Head' (the beginning)...
			Node<D>* newIterator = begin();
#ifndef NDEBUG
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tIterator set to the Head." << std::endl;
			std::cout << "DOUBLE LINK LIST DEBUG:\t\tSorting while-loop will now start." << std::endl;
#endif
			while (newIterator->nextNode != NULL) {
				newTemp = newIterator->nextNode;
#ifndef NDEBUG
				std::cout << "DOUBLE LINK LIST DEBUG:\t\t\tThe iterator node (" << counter << ") has not reached the end of the list, so it will be compared to temporary node [" << counter + 1 << "]." << std::endl;
#endif
				if (newIterator->data > newTemp->data) {
					swapped = true;
#ifndef NDEBUG
					std::cout << "DOUBLE LINK LIST DEBUG:\t\t\tIterator node (" << counter << ") is greater than temporary node [" << counter + 1 << "]." << std::endl;
#endif
					// Configuration 1
					if (newIterator == Head && newTemp == Tail) {
#ifndef NDEBUG
						std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\tConfiguration 1 triggered (Head is being compared to Tail)." << std::endl;
#endif
						// Set the temp node's 'previous' node as null (it will be the new Head)
						newTemp->previousNode = NULL;
						// Set the temp node's 'next' pointer to the iterator
						newTemp->nextNode = newIterator;
						// Set the iterator's 'previous' node as the temp node (it will be the new Tail)
						newIterator->previousNode = newTemp;
						// Set the iterator's 'next' node to NULL (it is the Tail)
						newIterator->nextNode = NULL;
						// Polarise the Head and Tail
						Head = newTemp;
						Tail = newIterator;
						newIterator = newIterator->nextNode;
#ifndef NDEBUG
						std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\tNode (" << counter << ") has swapped places with node [" << counter + 1 << "]; the Head swapped places with the Tail." << std::endl;
						std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\t'Swapped' set to 'true'." << std::endl;
						counter += 1;
#endif
					}

					// Configuration 2
					else if (newIterator != Head && newTemp != Tail) {
#ifndef NDEBUG
						std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\tConfiguration 2 triggered (A node other than the Head is being compared to a node other than the Tail)." << std::endl;
#endif
						// Set the temp node's 'previous' node to the iterator's previous node
						newTemp->previousNode = newIterator->previousNode;
						// Make the node before the iterator skip the iterator and go to the temp node (the new smaller node)
						newIterator->previousNode->nextNode = newTemp;
						// Update the pointer of the node AFTER the temp so that it points to the iterator
						newTemp->nextNode->previousNode = newIterator;
						// Make the iterator's 'next' pointer skip the temp node and go to the node after temp
						newIterator->nextNode = newTemp->nextNode;
						// Make the temp point forward to the iterator
						newTemp->nextNode = newIterator;
						// Make the iterator point backward to temp
						newIterator->previousNode = newTemp;
						newIterator = newIterator->nextNode;
#ifndef NDEBUG
						std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\tNode (" << counter << ") has swapped places with node [" << counter + 1 << "]." << std::endl;
						std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\t'Swapped' set to 'true'." << std::endl;
						counter += 1;
#endif
					}

					// Configuration 3
					else if (newIterator == Head && newTemp != Tail) {
#ifndef NDEBUG
						std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\tConfiguration 3 triggered (The Head is being compared to a node other than the Tail)." << std::endl;
#endif
						// Set the temp node's 'previous' node as null (it will be the new Head)
						newTemp->previousNode = NULL;
						// Make the iterator's 'previous' node point to the temp node
						newIterator->previousNode = newTemp;
						// Make the iterator's 'next' pointer skip the temp node and go to the node after temp
						newIterator->nextNode = newTemp->nextNode;
						// Update the pointer of the node AFTER the temp so that it points to the iterator
						newTemp->nextNode->previousNode = newIterator;
						// Make the temp point forward to the iterator
						newTemp->nextNode = newIterator;
						// Update the head
						Head = newTemp;
						newIterator = newIterator->nextNode;
#ifndef NDEBUG
						std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\tNode (" << counter << "), the previous Head, has swapped places with node [" << counter + 1 << "], the new Head." << std::endl;
						std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\t'Swapped' set to 'true'." << std::endl;
						counter += 1;
#endif
					}

					// Configuration 4
					else if (newIterator != Head && newTemp == Tail) {
#ifndef NDEBUG
						std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\tConfiguration 4 triggered (A node other than the Head is being compared to the Tail)." << std::endl;
#endif
						// Set the temp node's 'previous' node to the iterator's previous node
						newTemp->previousNode = newIterator->previousNode;
						// Make the node before the iterator skip the iterator and go to the temp node (the new smaller node)
						newIterator->previousNode->nextNode = newTemp;
						// Set the iterator's 'previous' node as the temp node (iterator will be the new Tail)
						newIterator->previousNode = newTemp;
						// Set the iterator node's 'next' node as null (it will be the new Tail)
						newIterator->nextNode = NULL;
						// Make the temp point forward to the iterator
						newTemp->nextNode = newIterator;
						// Update the head
						Tail = newIterator;
#ifndef NDEBUG
						std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\tNode (" << counter << ") has become the new Tail by swapping places with node [" << counter + 1 << "]." << std::endl;
						std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\t'Swapped' set to 'true'." << std::endl;
						counter += 1;
#endif
					}

					break;
				}

				else {
					newIterator = newIterator->nextNode;
#ifndef NDEBUG
					std::cout << "DOUBLE LINK LIST DEBUG:\t\t\tIterator (node " << counter << ") was not greater than the temp. node (" << counter + 1 << ")." << std::endl;
					std::cout << "DOUBLE LINK LIST DEBUG:\t\t\t\t'Swapped' set to 'false'." << std::endl;
					counter += 1;
#endif
				}
			}
		}

		// Repeat this loop from the start to the end of the nodes if there was 1 or more swaps. If there were no swaps, the loop will only run once because it is a 'do while' loop.
		while (swapped);
#ifndef NDEBUG
		std::cout << "DOUBLE LINK LIST DEBUG:\t\t\tSort is complete.\n" << std::endl;
#endif
	};
};