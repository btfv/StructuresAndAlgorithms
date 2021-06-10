#pragma once

template <typename T>
class ITree {
public:
	virtual void Insert(const T& key) {};
	virtual void Remove(const T& key) {};
	virtual bool Search(const T& key) { return 0; };
	virtual bool isEmpty() { return 0; };
};