#pragma once
#include <string>
#include <initializer_list>

class Vector {
public:
	Vector();
	Vector(const Vector& base);
	Vector(std::initializer_list<int> init_list);
	~Vector();

	int& operator[](unsigned int index);
	const int& Vector::operator[](unsigned int index) const;
	const Vector& operator=(const Vector & rhs);
	bool operator == (const Vector& rhs) const;
	bool operator != (const Vector& rhs) const;

	int * get_data();

	unsigned int get_capacity() const;
	unsigned int get_size() const;

	void Clear();
	void Insert(int value, unsigned int index);
	void PushBack(int value);
	int PopBack();
	
	std::string Stringify() const;

	const unsigned int kDefaultStartingCapacity = 8;
private:
	int * data;
	unsigned int size;
	unsigned int capacity;

	void Expand();
};

Vector InsertionSort(const Vector& vec);
