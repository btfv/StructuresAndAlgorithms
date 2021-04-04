#pragma once
#include <assert.h>
#include <iostream>
#include <fstream>
#include <cstring>

class Route {
private:
	int routeNumber;
	char* destination;
	int time_hours;
	int time_minutes;
	double price;
	int placesLeft;

	typedef struct {
		int routeNumber;
		char destination[30];
		int time_hours;
		int time_minutes;
		double price;
		int placesLeft;
	} DataToStore;
public:
	Route(std::ifstream& is);
	Route(int routeNumber, char* destination, int time_hours, int time_minutes, double price, int placesLeft);
	int getRouteNumber() { return routeNumber; }
	void setRouteNumber(int number) { this->routeNumber = number; };
	char* getDestination() { return destination; }
	double getPrice() { return price; }
	int getTimeHours() { return time_hours; }
	int getTimeMinutes() { return time_minutes; }
	int getPlacesLeft() { return placesLeft; }
	void setPlacesLeft(int placesLeft) { this->placesLeft = placesLeft; };

	bool writeToFile(std::ofstream& os);
	~Route() {}
};

class list_element {
private:
	Route* data;
	list_element* next;
	list_element* prev;
public:
	list_element(Route* data);
	list_element(Route* data, list_element* previous_element);
	~list_element();
	Route* getValue() { return data; }
	void setValue(Route* value);
	list_element* getPrev() { return prev; }
	void setPrev(list_element* element);
	list_element* getNext() { return next; }
	void setNext(list_element* element);

	friend std::ofstream& operator<< (std::ofstream&, const list_element&);
};

class linked_list {
private:
	int list_length;
	list_element* root;
	list_element* end;
public:
	linked_list();
	~linked_list();
	int get_length() { return list_length; };
	void insert(Route* flight_data);
	list_element* get_root() { return root; }
	friend std::ofstream& operator<< (std::ofstream&, const linked_list&);
};