#include "vector.h"

const unsigned int STARTING_CAPACITY = 8;

Vector::Vector() : data(new int[STARTING_CAPACITY]), size(0), capacity(STARTING_CAPACITY) {
}

Vector::~Vector() {
	delete[] data;
}

void Vector::push(int value) {
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

int Vector::pop() {
	this->size -= 1;
	return this->data[this->size];
	// todo reduce capacity when at 1:4 of size:capacity
}

std::string Vector::str() const {
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
