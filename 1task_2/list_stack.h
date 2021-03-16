#pragma once
#include <stdexcept>
#include "list_element.h"

class list_stack {
private:
	int list_length;
	list_element* root;
public:
	list_stack();
	~list_stack();
	int get_length() { return list_length; };
	void push_back(int data);
	void pop_back();
	bool is_empty();
	list_element* get_root() { return root; }
};