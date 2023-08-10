#include <iostream>
#include "memory.h"
#include "HashFunction.h"

using namespace HashFunction;

int main()
{
    // Create a pointer to a new instance of a hash table
    HashTable* table_01 = new HashTable;

    // Demonstrate that the hash table can add elements
    table_01->AddNewRecord("Zora", 34, 90001);    // No list at this hash index yet, create a new one, create a new double linked list inside the pair
    table_01->AddNewRecord("Zora", 34, 90000);    // List exists at this hash index but record isn't a duplicate so create it (will search prior 1 element)
    table_01->AddNewRecord("Zora", 34, 90002);    // List exists at this hash index but record isn't a duplicate so create it (will search prior 2 elements)
    table_01->AddNewRecord("Zora", 34, 90004);    // List exists at this hash index but record isn't a duplicate so create it (will search prior 3 elements)
    table_01->AddNewRecord("Zora", 34, 90005);    // List exists at this hash index but record isn't a duplicate so create it (will search prior 4 elements)
    table_01->AddNewRecord("Zora", 34, 90000);    // List exists at this hash index but record is a duplicate of node 2. Do not create.

    // Demonstrate that the hash table can remove elements
    table_01->RemoveItem(2);                                // Remove "Zora", 34, 900000
    table_01->RemoveRecord("Zora", 34, 90000);              // Doesn't exist so can't be removed.
    table_01->RemoveRecord("Zora Jane Kerr", 34, 90000);    // Doesn't exist so can't be removed.

    // Demonstrate that the hash table can print its elements
    table_01->PrintHashTable();

    table_01->AddNewRecord("Bob", 88, 1000000);    // No list at this hash index yet, create a new one, create a new double linked list inside the pair
    table_01->AddNewRecord("Alexandra", 12, 10000);    // List exists at this hash index but record isn't a duplicate so create it (will search prior 1 element)
    table_01->AddNewRecord("Geoffrey Miller", 50, 120000);    // List exists at this hash index but record isn't a duplicate so create it (will search prior 2 elements)
 
    // Demonstrate that the hash table can print its elements
    table_01->PrintHashTable();

    delete table_01;
    table_01 = nullptr;
}