#pragma once
class list_element {
private:
	int data;
	list_element* next;
public:
	list_element(int data);
	list_element(int data, list_element* next_element);
	int getValue() { return data; }
	void setValue(int value);
	list_element* getNext() { return next; }
	void setNext(list_element* element);
};
