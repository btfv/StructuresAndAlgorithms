#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>

template < typename T >
class list_element {
private:
	T data;
	list_element<T>* next;
	list_element<T>* prev;
public:
	list_element();
	list_element(T data);
	list_element(T data, list_element<T>* previous_element);
	~list_element();
	T getValue() { return data; }
	void setValue(T value);
	list_element<T>* getPrev() { return prev; }
	void setPrev(list_element<T>* element);
	list_element<T>* getNext() { return next; }
	void setNext(list_element<T>* element);

	friend std::ofstream& operator<< (std::ofstream&, const list_element<T>&);
	friend std::ifstream& operator>> (std::ifstream&, const list_element<T>&);
};

template < typename T >
list_element<T>::list_element() {
	this->data = 0;
	this->prev = 0;
	this->next = 0;
};
template < typename T >
list_element<T>::list_element(T data) {
	this->data = data;
	this->prev = 0;
	this->next = 0;
};
template < typename T >
list_element<T>::list_element(T data, list_element<T>* prev) {
	this->data = data;
	this->prev = prev;
	this->next = 0;
};
template < typename T >
list_element<T>::~list_element() {
	if (prev)
		prev->setNext(next);
	if (next)
		next->setPrev(prev);
}
template < typename T >
void list_element<T>::setNext(list_element<T>* next) {
	this->next = next;
}
template < typename T >
void list_element<T>::setPrev(list_element<T>* prev) {
	this->prev = prev;
}
template < typename T >
void list_element<T>::setValue(T value) {
	this->data = value;
}
template < typename T >
std::ofstream& operator<< (std::ofstream& stream, const list_element<T>& list_el) {
	stream.write((char&)&(this->data), sizeof(this->data));
	return stream;
}
template < typename T >
std::ifstream& operator>> (std::ifstream& stream, const list_element<T>& list_el) {
	stream.read((char&)&(this->data), sizeof(this->data));
	return stream;
}
