#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include "list_element.h"

template < typename T >
class linked_list {
private:
	int list_length;
	list_element<T>* root;
	list_element<T>* end;
public:
	linked_list();
	~linked_list();
	int get_length() { return list_length; };
	void insert(T&);
	void remove(const int index);
	list_element<T>* get_root() { return root; }
	friend std::ofstream& operator<< (std::ofstream&, const linked_list<T>*);
};

template <typename T>
void linked_list<T>::remove(const int index) {
	list_element<T>* curr = root;
	for (int i = 0; i < index; i++) {
		curr = root->getNext();
	}
	if (curr == nullptr) {
		return;
	}
	else if (curr == root) {
		root = curr->getNext();
	}
	else if (curr == end) {
		end = curr->getPrev();
	}
	delete curr;
}

template < typename T >
std::ofstream& operator<< (std::ofstream& stream, const linked_list<T>* list) {
	list_element<T>* curr = list.root;
	while (curr != NULL) {
		stream << *curr;
		curr = curr->getNext();
	};
	return stream;
}
template < typename T >
linked_list<T>::linked_list() {
	list_length = 0;
	root = 0;
	end = 0;
}
template < typename T >
linked_list<T>::~linked_list() {
	list_element<T>* curr = root;
	list_element<T>* next;
	while (curr != NULL) {
		next = curr->getNext();
		delete curr;
		curr = next;
	};
}
template < typename T >
void linked_list<T>::insert(T& data) {
	if (list_length == 0) {
		list_element<T>* new_element = new list_element<T>(data);
		root = new_element;
		end = root;
		list_length++;
		return;
	}
	list_element<T>* new_element = new list_element<T>(data, end);
	end->setNext(new_element);
	end = new_element;
	list_length++;
}