#pragma once
#include <tuple>
#include "PersonnelFile.h"

template<typename D>
class Node
{
public:
	// Default constructor
	Node() {
		std::cout << "Default Node constructor built." << std::endl;
	};

	// Destructor
	~Node() {};

	// Node navigation pointers
	Node<D>* previousNode;
	Node<D>* nextNode;

	// Node content variables
	D data;

	// A function for the template to call on the print function inside whatever its data type object is (this assumes one is defined)
	void Print() {
		data.Print();
	};
};