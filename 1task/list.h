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

	typedef struct DataToStore {
		int routeNumber;
		char destination[30];
		int time_hours;
		int time_minutes;
		double price;
		int placesLeft;
	} dataToStore;
public:
	Route(std::ifstream& is) {
		dataToStore data;
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
	Route(int routeNumber, char* destination, int time_hours, int time_minutes, double price, int placesLeft) {
		this->routeNumber = routeNumber;
		this->destination = destination;
		this->time_hours = time_hours;
		this->time_minutes = time_minutes;
		this->price = price;
		this->placesLeft = placesLeft;
	}
	int getRouteNumber() { return routeNumber; }
	void setRouteNumber(int number) { this->routeNumber = number; };
	char* getDestination() { return destination; }
	double getPrice() { return price; }
	int getTimeHours() { return time_hours; }
	int getTimeMinutes() { return time_minutes; }
	int getPlacesLeft() { return placesLeft; }
	void setPlacesLeft(int placesLeft) { this->placesLeft = placesLeft; };

	bool writeToFile(std::ofstream& os) {
		dataToStore data;
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
};