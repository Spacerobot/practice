#pragma once
#include <string>
#include <initializer_list>

class Vector {
public:
	Vector();
	Vector(std::initializer_list<int> init_list);
	~Vector();
	void PushBack(int value);
	int PopBack();
	std::string ToString() const;
	int& operator[](unsigned int index);
	unsigned int get_capacity() const;
	unsigned int get_size() const;
	const unsigned int kDefaultStartingCapacity = 8;
private:
	int * data;
	unsigned int size;
	unsigned int capacity;
};