#include "array_stack.h"

void array_stack::resize(const int new_size) {
	if (new_size <= elements_count) {
		return;
	}
	int* new_begin = new int[new_size];
	for (int i = 0; i < elements_count; i++) {
		new_begin[i] = begin[i];
	}
	delete[] begin;
	begin = new_begin;
	array_size = new_size;
}

array_stack::array_stack() {
	begin = new int[default_size];
	elements_count = 0;
	array_size = default_size;
}
array_stack::array_stack(const int size) {
	begin = new int[size];
	this->array_size = size;
	elements_count = 0;
}
int array_stack::back() {
	return *(begin + elements_count - 1);
}
bool array_stack::is_empty() {
	return elements_count == 0;
}
void array_stack::pop_back() {
	elements_count--;
}
void array_stack::push_back(int element) {
	if (elements_count >= array_size) {
		resize(array_size + default_size);
	}
	begin[elements_count] = element;
	elements_count++;
}
array_stack::~array_stack() {
	delete[] begin;
}