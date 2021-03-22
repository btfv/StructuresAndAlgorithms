#pragma once
template <typename T>
class array_stack {
private:
	T* begin;
	int elements_count;
	int array_size;
	const int default_size = 10;
	void resize(const int new_size);
public:
	array_stack();
	array_stack(const int size);
	T back();
	bool is_empty();
	void pop_back();
	void push_back(T element);
	~array_stack();
};

template <typename T>
void array_stack<T>::resize(const int new_size) {
	if (new_size <= elements_count) {
		return;
	}
	int* new_begin = new T[new_size];
	for (int i = 0; i < elements_count; i++) {
		new_begin[i] = begin[i];
	}
	delete[] begin;
	begin = new_begin;
	array_size = new_size;
}

template <typename T>
array_stack<T>::array_stack() {
	begin = new T[default_size];
	elements_count = 0;
	array_size = default_size;
}

template <typename T>
array_stack<T>::array_stack(const int size) {
	begin = new T[size];
	this->array_size = size;
	elements_count = 0;
}
template <typename T>
T array_stack<T>::back() {
	return *(begin + elements_count - 1);
}
template <typename T>
bool array_stack<T>::is_empty() {
	return elements_count == 0;
}
template <typename T>
void array_stack<T>::pop_back() {
	elements_count--;
}
template <typename T>
void array_stack<T>::push_back(T element) {
	if (elements_count >= array_size) {
		resize(array_size + default_size);
	}
	begin[elements_count] = element;
	elements_count++;
}
template <typename T>
array_stack<T>::~array_stack() {
	delete[] begin;
}