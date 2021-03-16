#pragma once

class array_stack {
private:
	int* begin;
	int elements_count;
	int array_size;
	const int default_size = 10;

	void resize(const int new_size);
public:
	array_stack();
	array_stack(const int size);
	int back();
	bool is_empty();
	void pop_back();
	void push_back(int element);
	~array_stack();
};