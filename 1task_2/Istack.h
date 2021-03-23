#pragma once

template<typename T>
class Istack {
public:
	virtual int get_length() = 0;
	virtual void push_back(T) = 0;
	virtual void pop_back() = 0;
	virtual bool is_empty() = 0;
	virtual T back() = 0;
};