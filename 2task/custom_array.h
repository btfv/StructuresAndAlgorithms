#pragma once
#include <assert.h>
#include <algorithm>

template <typename T>
class custom_array {
private:
	T* begin;
	int array_size;
	const int default_size = 10;
	void resize(const int new_size);
public:
	custom_array();
	explicit custom_array(const int);
	explicit custom_array(const int, const T&);
	T back();
	bool is_empty();
	void pop_back();
	void push_back(T element);
	int get_length() { return array_size; };
	~custom_array();

	T& operator[](const int);
	custom_array<T>& operator= (const custom_array<T>&);
};

template <typename T>
T& custom_array<T>::operator[](const int index) {
	return begin[index];
}

template <typename T>
void custom_array<T>::resize(const int new_size) {
	int* new_begin = new T[new_size];
	for (int i = 0; i < std::min(array_size, new_size); i++) {
		new_begin[i] = begin[i];
	}
	delete[] begin;
	begin = new_begin;
	array_size = new_size;
}

template <typename T>
custom_array<T>::custom_array() {
	begin = new T[default_size];
	array_size = default_size;
}

template <typename T>
custom_array<T>::custom_array(const int size) {
	begin = new T[size];
	array_size = size;
}
template <typename T>
T custom_array<T>::back() {
	return *(begin + array_size - 1);
}
template <typename T>
bool custom_array<T>::is_empty() {
	return array_size == 0;
}
template <typename T>
custom_array<T>::custom_array(const int size, const T& initial) {
	begin = new T[size];
	array_size = size;
	
	for (int i = 0; i < size; i++) {
		begin[i] = initial;
	}
}
template <typename T>
void custom_array<T>::pop_back() {
	resize(array_size - 1);
}
template <typename T>
void custom_array<T>::push_back(T element) {
	resize(array_size + 1);
	begin[array_size - 1] = element;
}
template <typename T>
custom_array<T>::~custom_array() {
	delete[] begin;
}

template<class T>
custom_array<T>& custom_array<T>::operator= (const custom_array<T>& v)
{
	delete[] begin;
	array_size = v.array_size;
	begin = new T[array_size];
	for (unsigned int i = 0; i < array_size; i++)
		begin[i] = v.begin[i];
	return *this;
}