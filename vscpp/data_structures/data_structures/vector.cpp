#include "vector.h"
#include <algorithm>

Vector::Vector() : data(new int[Vector::kDefaultStartingCapacity]), size(0), capacity(Vector::kDefaultStartingCapacity) {
}

Vector::Vector(std::initializer_list<int> init_list) : data(new int[init_list.size()]), size(init_list.size()), capacity(init_list.size())
{
	std::copy(init_list.begin(), init_list.end(), this->data);
}

Vector::~Vector() {
	delete[] data;
}

void Vector::PushBack(int value) {
	int new_size = this->size + 1;
	if (new_size > this->capacity) {
		int new_capacity = this->capacity * 2;
		int * new_array = new int[new_capacity];
		for (int i = 0; i < this->size; ++i) {
			new_array[i] = this->data[i];
		}
		delete[] this->data;
		this->data = new_array;
		this->capacity = new_capacity;
	}
	this->data[this->size] = value;
	this->size = new_size;
}

int Vector::PopBack() {
	this->size -= 1;
	return this->data[this->size];
}

std::string Vector::ToString() const {
	std::string result;
	for (unsigned int i = 0; i < this->size; ++i) {
		result += std::to_string(this->data[i]);
		result += ", ";
	}
	return result;
}

int& Vector::operator[](unsigned int index) {
	return this->data[index];
}

unsigned int Vector::get_capacity() const {
	return this->capacity;
}

unsigned int Vector::get_size() const {
	return this->size;
}
