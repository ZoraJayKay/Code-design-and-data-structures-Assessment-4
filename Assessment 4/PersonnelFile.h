#pragma once

// A struct to replace the standard data value to be stored within each node of each double linked list of the hash table
struct PersonnelRecord {
	const char* name;
	unsigned int age;
	unsigned int salary;

	// An overloaded operator for making the record that calls it equal to another nominated record
	void operator = (const PersonnelRecord rhs) {
		this->name = rhs.name;
		this->age = rhs.age;
		this->salary = rhs.salary;
	};

	// An overloaded operator for checking whether the record that calls it is identical to another nominated record
	bool operator == (const PersonnelRecord rhs) {
		// If any of the record particulars are different, return that they do not match (false)
		if (!(this->name == rhs.name) || !(this->age == rhs.age) || !(this->salary == rhs.salary)) {
			return false;
		}
		// Otherwise return that they do match (true)
		return true;
	};

	// A function for printing this one personnel record to the console
	void Print() {
		//std::cout << "\tName:\t[" << this->name << "]\n\t\t\t\t\t\t\t\tAge:\t[" << this->age << "]\n\t\t\t\t\t\t\t\tSalary:\t[" << this->salary << "].\n" << std::endl;
		std::cout << "\tName: [" << this->name << "]\tAge: [" << this->age << "]\tSalary: [" << this->salary << "]." << std::endl;
	};
};