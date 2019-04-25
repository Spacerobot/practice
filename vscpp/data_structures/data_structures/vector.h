#pragma once
#include <string>

class Vector {
public:
	Vector();
	~Vector();
	void push(int value);
	int pop();
	std::string str();
	int operator[](unsigned int index);
private:
	int * data;
	unsigned int size;
	unsigned int capacity;
};