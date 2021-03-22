#pragma once
#include <stdexcept>
#include "list_element.h"

template <typename T>
class list_stack {
private:
	int list_length;
	list_element<T>* root;
public:
	list_stack();
	~list_stack();
	int get_length() { return list_length; };
	void push_back(T data);
	void pop_back();
	bool is_empty();
	T back() { return root->getValue(); }
};

template <typename T>
list_stack<T>::list_stack() {
	root = 0;
	list_length = 0;
}

template <typename T>
list_stack<T>::~list_stack() {
	list_element<T>* el = root;
	list_element<T>* next;
	while (el != 0) {
		next = el->getNext();
		delete el;
		el = next;
	};
}

template <typename T>
void list_stack<T>::push_back(T data) {
	list_element<T>* new_el = new list_element<T>(data);
	new_el->setNext(this->root);
	this->root = new_el;
	list_length++;
}

template <typename T>
void list_stack<T>::pop_back() {
	if (list_length == 0) {
		return;
	}
	list_element<T>* next = root->getNext();
	delete root;
	root = next;
	list_length--;
}

template <typename T>
bool list_stack<T>::is_empty() {
	return this->list_length == 0;
}
