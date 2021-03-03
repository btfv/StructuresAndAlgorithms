﻿#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <fstream>
#include <cstring>
#include "list.h"
#define FLIGHTS_IN_FILE 55
#define FLIGHTS_PER_PAGE 10

void createBinaryFile(char*);
void removeFlightMenu(linked_list*);
void addStruct(std::ofstream&, int);
Route* generateStruct(int);
void mainMenu(linked_list*);
void changeTicketsQuantityMenu(linked_list*);
void changeTicketsQuantity(linked_list*, const int*, const int*);
void getFlightInfoMenu(linked_list*);
void getFlightInfo(linked_list*, const int*);
void getFlightsInfo(linked_list*, int);
void getFlightsInfoMenu(linked_list*);
void printLine();
bool if_file_exists(char*);
linked_list* readBinaryFile(char*);

int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "Russian");
	srand((unsigned int)time(NULL));
	char* path;
	if (argc > 1) {
		path = argv[1];
	}
	else {
		path = new char[30];
		printf("Enter filename: ");
		scanf("%s", path);
	}

	if (!if_file_exists(path)) {
		createBinaryFile(path);
	}

	linked_list* list = readBinaryFile(path);
	mainMenu(list);
	delete list;
	return 0;
}

linked_list* readBinaryFile(char* path) {
	linked_list* list = new linked_list();
	std::ifstream ifs(path, std::ios::binary);

	assert(ifs.is_open());

	while (!ifs.eof()) {
		Route* route = new Route(ifs);
		if(!ifs.eof())
			list->insert(route);
	}
	ifs.close();
	return list;
}

void createBinaryFile(char* name) {
	std::ofstream ofs(name, std::ios::binary);
	if (ofs)
		for (int i = 0; i < FLIGHTS_IN_FILE; i++) {
			addStruct(ofs, i + 1);
		}
	ofs.close();
}

void addStruct(std::ofstream& fp, int rNum) {
	Route* str = generateStruct(rNum);
	str->writeToFile(fp);
	delete str;
}

Route* generateStruct(int rNum) {
	int routeNumber = rNum;
	int i = 0;
	char* destination = new char[30];
	while (i < 5 || (rand() % 10 > 1 && i < 30 - 2)) {
		destination[i] = (char)'а' + (char)rand() % 20;
		if (rand() % 10 == 1 && i > 1 && destination[i - 1] != ' ' && destination[i - 2] != ' ') {
			destination[i] = ' ';
		}
		i++;
	}
	destination[i] = '\0';
	int time_hours = rand() % 24;
	int time_minutes = rand() % 60;
	double price = rand() % 100000 + (double)((rand() % 100) / 100);
	int placesLeft = rand() % 1000;
	return new Route(routeNumber, destination, time_hours, time_minutes, price, placesLeft);
}

bool if_file_exists(char* name)
{
	FILE* file;
	if (file = fopen(name, "r")) {
		fclose(file);
		return 1;
	}
	return 0;
}

void mainMenu(linked_list* list) {
	int num = 0;
	do {
		system("CLS");
		printf("1. Изменение количества билетов\n");
		printf("2. Получение информации по рейсу\n");
		printf("3. Получение списка рейсов\n");
		printf("4. Удалить рейс\n");
		printf("0. Выход\n");
		num = _getch() - '0';

		switch (num) {
		case 1: changeTicketsQuantityMenu(list); break;
		case 2: getFlightInfoMenu(list); break;
		case 3: getFlightsInfoMenu(list); break;
		case 4: removeFlightMenu(list);
		}
	} while (num != 0);
}

bool if_file_exist(char* name) {
	struct stat buffer;
	return (stat(name, &buffer) == 0);
}

void changeTicketsQuantityMenu(linked_list* list) {
	int routeNumber = -1;
	int ticketsSold = -1;

	int num = -1;
	do {
		system("CLS");
		if (routeNumber == -1)
			printf("1. Ввести номер рейса\n");
		else
			printf("1. Номер рейса введён (%d)\n", routeNumber);
		if (ticketsSold == -1)
			printf("2. Ввести количество проданных билетов\n");
		else
			printf("2. Количество проданных билетов введено (%d)\n", ticketsSold);
		printf("3. Изменить количество\n");
		printf("0. Назад\n");
		num = _getch() - '0';

		switch (num) {
		case 1: printLine(); printf("Введите номер рейса: ");  scanf("%d%*c", &routeNumber); break;
		case 2: printLine(); printf("Введите количество проданных билетов: ");  scanf("%d%*c", &ticketsSold); break;
		case 3: if (routeNumber >= 0 && ticketsSold > 0) {
					changeTicketsQuantity(list, &routeNumber, &ticketsSold);
					return;
				}
				else {
					printLine();
					printf("Введены не все данные!");
					scanf("%*c");
				}
				break;
		case 0: return;
		}
	} while (1);
}

void changeTicketsQuantity(linked_list* list, const int* routeNumber, const int* ticketsSold) {
	list_element* flight = list->get_root();
	while (flight->getValue()->getRouteNumber() != *routeNumber && flight->getNext() != 0) {
		flight = flight->getNext();
	}
	if (flight->getValue()->getRouteNumber() == *routeNumber) {
		int placesLeft = flight->getValue()->getPlacesLeft();
		if (placesLeft - *ticketsSold < 0) {
			printf("Количество купленных билетов больше количества свободных мест!");
			scanf("%*c");
			return;
		}
		flight->getValue()->setPlacesLeft(placesLeft - *ticketsSold);
		printf("Количество свободных мест изменено");
		scanf("%*c");
		return;
	}
	printf("Рейс с таким номером не найден!");
	scanf("%*c");
}

void getFlightInfoMenu(linked_list* list) {
	int routeNumber = -1;
	int ticketsSold = -1;

	int num = -1;
	do {
		system("CLS");
		if (routeNumber == -1)
			printf("1. Ввести номер рейса\n");
		else
			printf("1. Номер рейса введён (%d)\n", routeNumber);
		printf("2. Получить информацию по рейсу\n");
		printf("0. Назад\n");
		num = _getch() - '0';

		switch (num) {
		case 0: break;
		case 1: printLine(); printf("Введите номер рейса: ");  scanf("%d%*c", &routeNumber); break;
		case 2: printLine(); if (routeNumber >= 0) {
			getFlightInfo(list, &routeNumber);
			num = _getch() - '0';
		}
			  else {
			printf("Введены не все данные!");
			scanf("%*c");
		}
			  break;
		}
	} while (num != 0);
}

void getFlightInfo(linked_list* list, const int* routeNumber) {
	list_element* flight = list->get_root();

	while (flight->getValue()->getRouteNumber() != *routeNumber && flight->getNext() != 0) {
		flight = flight->getNext();
	}
	if (flight->getValue()->getRouteNumber() == *routeNumber) {
		printf("| N |          Направление         |Время|  Цена  |Мест|\n");
		printLine();
		printf("|%03d|%30s|%02d:%02d|%08.02lf|%04d|\n", flight->getValue()->getRouteNumber(), flight->getValue()->getDestination(), flight->getValue()->getTimeHours(), flight->getValue()->getTimeMinutes(), flight->getValue()->getPrice(), flight->getValue()->getPlacesLeft());
		printLine();
		return;
	}
	printf("Рейс с таким номером не найден!\n");
}

void getFlightsInfoMenu(linked_list* list) {
	int page = 1;
	int num = 0;
	const int pagesInFile = (FLIGHTS_IN_FILE + FLIGHTS_PER_PAGE - 1) / FLIGHTS_PER_PAGE;
	do {
		system("CLS");
		printf("Листание страниц кнопками вверх и вниз\n");
		printf("0. Назад\n");
		printLine();
		printf("Страница %d из %d\n", page, pagesInFile);
		getFlightsInfo(list, page);
		num = _getch();
		switch (num) {
		case 48: break;
		case 72: page++; break;
		case 80: page--; break;
		}
		if (page < 1) {
			page = 1;
		}
		if (page > pagesInFile) {
			page = pagesInFile;
		}
	} while (num != 48);
}

void getFlightsInfo(linked_list* list, int page) {
	list_element* flight = list->get_root();
	printLine();
	printf("| N |          Направление         |Время|  Цена  |Мест|\n");
	printLine();

	int number = 0;
	while (flight != 0 && number < page * FLIGHTS_PER_PAGE) {
		if (number >= (page - 1) * FLIGHTS_PER_PAGE)
			printf("|%03d|%30s|%02d:%02d|%08.02lf|%04d|\n", flight->getValue()->getRouteNumber(), flight->getValue()->getDestination(), flight->getValue()->getTimeHours(), flight->getValue()->getTimeMinutes(), flight->getValue()->getPrice(), flight->getValue()->getPlacesLeft());
		flight = flight->getNext();
		number++;
	}
	printLine();
}

void removeFlightMenu(linked_list* list) {
	int routeNumber = -1;
	int ticketsSold = -1;

	int num = -1;

	do {
		system("CLS");
		if (routeNumber == -1)
			printf("1. Ввести номер рейса\n");
		else
			printf("1. Номер рейса введён (%d)\n", routeNumber);
		printf("2. Удалить рейс\n");
		printf("0. Назад\n");
		num = _getch() - '0';

		switch (num) {
		case 0: break;
		case 1: printLine(); printf("Введите номер рейса: ");  scanf("%d%*c", &routeNumber); break;
		case 2: printLine(); if (routeNumber >= 0) {
			list_element* element = list->get_root();
			while (element->getValue()->getRouteNumber() != routeNumber && element != 0) {
				element = element->getNext();
			}
			if (element == 0) {
				printf("Рейс с таким номером не найден!\n");
				num = _getch() - '0';
				return;
			}
			delete element;
			printf("Рейс успешно удален!\n");
			num = _getch() - '0';
		}
			  else {
			printf("Введены не все данные!");
			scanf("%*c");
		}
			  break;
		}
	} while (num != 0);
}
void printLine() {
	printf("--------------------------------------------------------\n");
}