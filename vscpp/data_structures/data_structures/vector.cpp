#include "vector.h"
#include <algorithm> // copy, 
#include <cassert>
#include <vector>

Vector::Vector() : data(new int[Vector::kDefaultStartingCapacity]), size(0), capacity(Vector::kDefaultStartingCapacity) {
}

Vector::Vector(const Vector& rhs) : data(new int[rhs.get_capacity()]), size(rhs.get_size()), capacity(rhs.get_capacity()) {
	std::copy(rhs.data, rhs.data + rhs.size, this->data);
}

Vector::Vector(std::initializer_list<int> init_list) : data(new int[init_list.size()]), size(init_list.size()), capacity(init_list.size()) {
	std::copy(init_list.begin(), init_list.end(), this->data);
}

Vector::~Vector() {
	delete[] data;
}

int& Vector::operator[](unsigned int index) {
	assert(index < this->size);
	return this->data[index];
}

const int& Vector::operator[](unsigned int index) const {
	assert(index < this->size);
	return this->data[index];
}

const Vector& Vector::operator=(const Vector & rhs) {
	delete[] this->data;
	this->data = new int[rhs.get_capacity()];
	this->size = rhs.size;
	this->capacity = rhs.capacity;
	std::copy(rhs.data, rhs.data + rhs.size, this->data);
	return *this;
}

bool Vector::operator==(const Vector & rhs) const {
	bool result = true;
	if (this->get_size() != rhs.get_size()) {
		result = false;
	}
	else {
		for (unsigned int i = 0; i < this->get_size(); ++i) {
			if ((*this)[i] != rhs[i]) {
				result = false;
				break;
			}
		}
	}
	return result;

}

bool Vector::operator!=(const Vector & rhs) const {
	return !((*this) == rhs);
}

int * Vector::get_data()
{
	return data;
}

int * Vector::begin()
{
	return this->data;
}

int * Vector::end()
{
	return this->data + this->size;
}

const int * Vector::begin() const
{
	return this->data;
}

const int * Vector::end() const
{
	return this->data + this->size;
}

unsigned int Vector::get_capacity() const {
	return this->capacity;
}

unsigned int Vector::get_size() const {
	return this->size;
}

void Vector::Clear() {
	this->size = 0;
}

void Vector::Insert(int value, unsigned int index) {
	assert(index <= this->size);
	int insert_value = value;
	for (unsigned int i = index; i < this->size; ++i) {
		int temp = data[i];
		data[i] = insert_value;
		insert_value = temp;
	}
	this->PushBack(insert_value);
}

void Vector::PushBack(int value) {
	int new_size = this->size + 1;
	if (new_size > this->capacity) {
		this->Expand();
	}
	this->data[this->size] = value;
	this->size = new_size;
}

int Vector::PopBack() {
	assert(this->get_size() > 0);
	this->size -= 1;
	return this->data[this->size];
}

std::string Vector::Stringify() const {
	std::string result;
	for (unsigned int i = 0; i < this->get_size(); ++i) {
		result += std::to_string(this->data[i]);
		result += ", ";
	}
	return result;
}

void Vector::Expand() {
	int new_capacity = this->capacity * 2;
	int * new_array = new int[new_capacity];
	std::copy(this->data, this->data + this->size, new_array);
	delete[] this->data;
	this->data = new_array;
	this->capacity = new_capacity;
}

Vector InsertionSort(const Vector& vec) {
	if (vec.get_size() < 2) {
		return vec;
	}

	// seeding the sorted vector
	Vector result;
	result.PushBack(vec[0]);

	for (unsigned int unsorted_index = 1; unsorted_index < vec.get_size(); ++unsorted_index) {
		unsigned int sorted_index = 0;
		while (sorted_index < result.get_size()) {
			if (vec[unsorted_index] < result[sorted_index])
				break;
			sorted_index++;
		}
		result.Insert(vec[unsorted_index], sorted_index);
	}
	return result;
}

// Helper
Vector Merge(const Vector& left, const Vector& right) {
	Vector result;
	auto * l_iter = left.begin();
	auto * r_iter = right.begin();
	while (l_iter < left.end() || r_iter < right.end()) {
		if (l_iter != left.end() && (r_iter == right.end() || *l_iter < *r_iter)) {
			result.PushBack(*l_iter);
			++l_iter;
		}
		else {
			result.PushBack(*r_iter);
			++r_iter;
		}
	}
	return result;
}

Vector MergeSort(const Vector & vec)
{
	if (vec.get_size() < 2) {
		return vec;
	}
	std::vector<Vector> vectors;
	for (auto && element : vec) {
		vectors.push_back(Vector({ element }));
	}
	while (vectors.size() > 1) {
		std::vector<Vector> next_level;
		for (unsigned int index = 0; index < vectors.size() - 1; index += 2) {
			next_level.push_back(Merge(vectors[index], vectors[index + 1]));
		}
		// as its merged by pairs an odd-sized vector would cause the last element not to be merged
		if (vectors.size() % 2 != 0) {
			*next_level.rbegin() = Merge(*next_level.rbegin(), *vectors.rbegin());
		}
		vectors = next_level;
	}

	return vectors[0];
}

void SiftDown(Vector& heap, int index) {
	const unsigned int l_child = index * 2 + 1;
	const unsigned int r_child = index * 2 + 2;
	if (l_child < heap.get_size()) {
		if (r_child < heap.get_size() && heap[r_child] > heap[l_child]) {
			if (heap[r_child] > heap[index]) {
				std::swap(heap[r_child], heap[index]);
				SiftDown(heap, r_child);
			}
		}
		else if (heap[l_child] > heap[index]) {
			std::swap(heap[l_child], heap[index]);
			SiftDown(heap, l_child);
		}
	}
}

Vector Heapify(const Vector & vec) {
	Vector heap(vec);
	for (int index = heap.get_size() / 2; index >= 0; --index) {
		SiftDown(heap, index);
	}
	return heap;
}

Vector HeapSort(const Vector & vec) {
	if (vec.get_size() < 2) {
		return vec;
	}
	Vector result = Heapify(vec);
	assert(std::is_heap(result.begin(), result.end()));
	// place item towards end
	for (unsigned int heap_size = result.get_size(); heap_size > 1; --heap_size) {
		std::swap(result[0], result[heap_size - 1]);
		SiftDown(result, 0);
	}
	return result;
}
