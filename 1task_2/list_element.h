#pragma once
template <typename T>
class list_element {
private:
	T data;
	list_element<T>* next;
public:
	list_element(T data);
	list_element(T data, list_element<T>* next_element);
	T getValue() { return data; }
	void setValue(T value);
	list_element<T>* getNext() { return next; }
	void setNext(list_element<T>* element);
};

template <typename T>
list_element<T>::list_element(T data) {
	this->data = data;
	this->next = 0;
};

template <typename T>
list_element<T>::list_element(T data, list_element<T>* next) {
	this->data = data;
	this->next = next;
};

template <typename T>
void list_element<T>::setNext(list_element<T>* next) {
	this->next = next;
};

template <typename T>
void list_element<T>::setValue(T value) {
	this->data = value;
};