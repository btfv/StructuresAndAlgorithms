#pragma once
#include <assert.h>
#include "list.h"

//List Element

list_element::list_element(Route* data) {
	this->data = data;
	this->prev = 0;
	this->next = 0;
};

list_element::list_element(Route* data, list_element* prev) {
	this->data = data;
	this->prev = prev;
	this->next = 0;
};

list_element::~list_element() {
	if(prev)
		prev->setNext(next);
	if(next)
		next->setPrev(prev);
}

void list_element::setNext(list_element* next) {
	this->next = next;
}

void list_element::setPrev(list_element* prev) {
	this->prev = prev;
}

void list_element::setValue(Route* value) {
	this->data = value;
}
//Linked List

linked_list::linked_list() {
	list_length = 0;
	root = 0;
	end = 0;
}

linked_list::~linked_list() {
	list_element* curr = root;
	list_element* next;
	while (curr != NULL) {
		next = curr->getNext();
		delete curr;
		curr = next;
	};
}

void linked_list::insert(Route* data) {
	if (list_length == 0) {
		list_element* new_element = new list_element(data);
		root = new_element;
		end = root;
		list_length++;
		return;
	}
	list_element* new_element = new list_element(data, end);
	end->setNext(new_element);
	end = new_element;
	list_length++;
}

// Route Element

Route::Route(int routeNumber, char* destination, int time_hours, int time_minutes, double price, int placesLeft) {
	this->routeNumber = routeNumber;
	this->destination = destination;
	this->time_hours = time_hours;
	this->time_minutes = time_minutes;
	this->price = price;
	this->placesLeft = placesLeft;
}

Route::Route(std::ifstream& is) {
	DataToStore data;
	is.read((char*)&data, sizeof(data));

	this->routeNumber = data.routeNumber;
	this->destination = new char[30];
	int i = 0;
	do {
		this->destination[i] = data.destination[i];
		i++;
	} while (data.destination[i - 1] != '\0');
	this->time_hours = data.time_hours;
	this->time_minutes = data.time_minutes;
	this->price = data.price;
	this->placesLeft = data.placesLeft;
}

bool Route::writeToFile(std::ofstream& os) {
	DataToStore data;
	data.routeNumber = this->routeNumber;
	data.time_hours = this->time_hours;
	data.time_minutes = this->time_minutes;
	data.price = this->price;
	data.placesLeft = this->placesLeft;
	int i = 0;
	do {
		data.destination[i] = this->destination[i];
		i++;
	} while (destination[i - 1] != '\0');
	os.write((char*)&data, sizeof(data));
	return os.good();
}