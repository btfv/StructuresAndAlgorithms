#include "list_element.h"
list_element::list_element(int data) {
	this->data = data;
	this->next = 0;
};

list_element::list_element(int data, list_element* next) {
	this->data = data;
	this->next = next;
};

void list_element::setNext(list_element* next) {
	this->next = next;
}

void list_element::setValue(int value) {
	this->data = value;
}