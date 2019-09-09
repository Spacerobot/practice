#pragma once
#include <string>

class Vector {
public:
	Vector();
	~Vector();
	void PushBack(int value);
	int PopBack();
	std::string ToString() const;
	int& operator[](unsigned int index);
	unsigned int get_capacity() const;
	unsigned int get_size() const;
	const unsigned int kStartingCapacity = 8;
private:
	int * data;
	unsigned int size;
	unsigned int capacity;
};