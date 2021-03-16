#include "list_stack.h"

list_stack::list_stack() {
	root = 0;
	list_length = 0;
}
list_stack::~list_stack() {
	list_element* el = root;
	list_element* next;
	while (el != 0) {
		next = el->getNext();
		delete el;
		el = next;
	};
}
void list_stack::push_back(int data) {
	list_element* new_el = new list_element(data);
	new_el->setNext(this->root);
	this->root = new_el;
	list_length++;
}
void list_stack::pop_back() {
	if (list_length == 0) {
		return;
	}
	list_element* next = root->getNext();
	delete root;
	root = next;
	list_length--;
}
bool list_stack::is_empty(){
	return this->list_length == 0;
}
