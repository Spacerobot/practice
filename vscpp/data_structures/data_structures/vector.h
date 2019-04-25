#pragma once
#include <string>

class Vector {
public:
	Vector();
	~Vector();
	void push(int value);
	int pop();
	std::string str() const;
	int& operator[](unsigned int index);
	unsigned int get_capacity() const;
	unsigned int get_size() const;
private:
	int * data;
	unsigned int size;
	unsigned int capacity;
};