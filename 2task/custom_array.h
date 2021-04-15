#pragma once
#include <assert.h>
#include <algorithm>
#include <fstream>

template <typename T>
class custom_array {
private:
	T* begin;
	int array_size;
	int length;
public:
	custom_array();
	custom_array(const int);
	custom_array(const int, const T&);
	T& back();
	bool is_empty();
	void pop_back();
	void push_back(T&);
	int get_length() { return length; };
	~custom_array();
	void resize(const int new_size);

	T& operator[](const int);
	custom_array<T>& operator= (const custom_array<T>&);

	friend std::ofstream& operator<< (std::ofstream&, const custom_array<T>&);
};

template <typename T>
std::ofstream& operator<< (std::ofstream& stream, const custom_array<T>& arr) {
	for (int i = 0; i < arr.length; i++) {
		stream.write((char*)&arr[i], sizeof(arr[i]));
	}
	return stream;
};

template <typename T>
T& custom_array<T>::operator[](const int index) {
	return begin[index];
}

template <typename T>
void custom_array<T>::resize(const int new_size) {
	T* new_begin = new T[new_size];
	for (int i = 0; i < std::min(array_size, new_size); i++) {
		new_begin[i] = begin[i];
	}
	if(begin)
		delete[] begin;
	begin = new_begin;
	array_size = new_size;
	length = std::min(length, new_size);
}

template <typename T>
custom_array<T>::custom_array() {
	begin = 0;
	array_size = 0;
	length = 0;
}

template <typename T>
custom_array<T>::custom_array(const int size) {
	begin = new T[size];
	array_size = size;
	length = size;
}
template <typename T>
T& custom_array<T>::back() {
	assert(length > 0);
	return begin[length - 1];
}
template <typename T>
bool custom_array<T>::is_empty() {
	return length == 0;
}
template <typename T>
custom_array<T>::custom_array(const int size, const T& initial) {
	begin = new T[size];
	array_size = size;
	length = size;

	for (int i = 0; i < size; i++) {
		begin[i] = initial;
	}
}
template <typename T>
void custom_array<T>::pop_back() {
	length--;
}
template <typename T>
void custom_array<T>::push_back(T& element) {
	if (length + 1 > array_size)
		resize(array_size + 1);
	begin[length] = element;
	length++;
}
template <typename T>
custom_array<T>::~custom_array() {
	delete[] begin;
}

template<class T>
custom_array<T>& custom_array<T>::operator= (const custom_array<T>& v)
{
	if (this == &v)
		return *this;
	delete[] begin;
	array_size = v.array_size;
	length = v.length;
	begin = new T[array_size];
	for (int i = 0; i < array_size; i++)
		begin[i] = v.begin[i];
	return *this;
}