#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
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
void addRouteToFile(std::ofstream&, int);
Route* generateRoute(int);
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
void clearFile(char*);
void writeToBinFile(char*, linked_list*);
void changeDestination(linked_list*);
void insertNewElement(linked_list*);

template<typename T>
void inputProtection(T& variable) {
	while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{
		T a;
		std::cin >> a;

		// Проверка на предыдущее извлечение
		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			std::cout << "Невалидно\n";
		}
		else
		{
			std::cin.ignore(32767, '\n'); // удаляем лишние значения
			variable = a;
			return;
		}
	}
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	srand((unsigned int)time(NULL));
	char* path;
	if (argc > 1) {
		path = argv[1];
	}
	else {
		path = new char[30];
		printf("Введите путь к файлу: ");
		scanf("%s", path);
	}

	if (!if_file_exists(path)) {
		createBinaryFile(path);
	}

	linked_list* list = readBinaryFile(path);
	mainMenu(list);

	clearFile(path);
	writeToBinFile(path, list);

	delete list;
	return 0;
}

void clearFile(char* path) {
	std::ofstream ofs;
	ofs.open(path, std::ofstream::out | std::ofstream::trunc);
	assert(ofs.is_open());
	ofs.close();
}

void writeToBinFile(char* path, linked_list* list) {
	std::ofstream ofs(path, std::ios::binary);
	assert(ofs.is_open());

	ofs << *list;
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
			addRouteToFile(ofs, i + 1);
		}
	ofs.close();
}

void addRouteToFile(std::ofstream& fp, int rNum) {
	Route* str = generateRoute(rNum);
	str->writeToFile(fp);
	delete str;
}

Route* generateRoute(int rNum) {
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
		printf("5. Изменить название рейса\n");
		printf("6. Добавить рейс\n");
		printf("0. Выход\n");
		num = _getch() - '0';
		if (num < 0 || num > 9) {
			num = -1;
		}

		switch (num) {
		case 1: changeTicketsQuantityMenu(list); break;
		case 2: getFlightInfoMenu(list); break;
		case 3: getFlightsInfoMenu(list); break;
		case 4: removeFlightMenu(list); break;
		case 5: changeDestination(list); break;
		case 6: insertNewElement(list); break;
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
		if (num < 0 || num > 9) {
			num = -1;
		}

		switch (num) {
		case 1: printLine(); printf("Введите номер рейса: ");  inputProtection<int>(routeNumber); break;
		case 2: printLine(); printf("Введите количество проданных билетов: "); inputProtection<int>(ticketsSold); break;
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
	if (*ticketsSold < 0) {
		printf("Количество проданных билетов не может быть отрицательным!");
		scanf("%*c");
		return;
	}
	if (*routeNumber < 0) {
		printf("Номер рейса не может быть отрицательным!");
		scanf("%*c");
		return;
	}
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
		if (num < 0 || num > 9) {
			num = -1;
		}

		switch (num) {
		case 0: break;
		case 1: printLine(); printf("Введите номер рейса: "); inputProtection<int>(routeNumber); break;
		case 2: printLine(); if (routeNumber >= 0) {
			getFlightInfo(list, &routeNumber);
			num = _getch() - '0';
			if (num < 0 || num > 9) {
				num = -1;
			}
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
	if (*routeNumber < 0) {
		printf("Номер рейса не может быть отрицательным!");
		scanf("%*c");
		return;
	}
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
		if (num < 0 || num > 9) {
			num = -1;
		}
		switch (num) {
		case 0: break;
		case 1: printLine(); printf("Введите номер рейса: "); inputProtection<int>(routeNumber); break;
		case 2: printLine(); if (routeNumber >= 0) {
			list_element* element = list->get_root();
			while (element != 0 && element->getValue()->getRouteNumber() != routeNumber) {
				element = element->getNext();
			}
			if (element == 0) {
				printf("Рейс с таким номером не найден!\n");
				num = _getch() - '0';
				if (num < 0 || num > 9) {
					num = -1;
				}
				return;
			}
			if (element == list->get_root()) {
				list->remove_root();
			}
			else if (element == list->get_end()) {
				list->remove_end();
			}
			else
				delete element;
			printf("Рейс успешно удален!\n");
			num = _getch() - '0';
			if (num < 0 || num > 9) {
				num = -1;
			}
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

void changeDestination(linked_list* list) {
	int routeNumber = -1;
	char* new_dist = new char[30];
	new_dist[0] = '\0';
	int num = -1;
	do {
		system("CLS");
		if (routeNumber == -1)
			printf("1. Ввести номер рейса\n");
		else
			printf("1. Номер рейса введён (%d)\n", routeNumber);
		if (new_dist[0] == '\0')
			printf("2. Ввести направление\n");
		else
			printf("2. Направление введено (%s)\n", new_dist);
		printf("3. Изменить направление\n");
		printf("0. Назад\n");
		num = _getch() - '0';
		if (num < 0 || num > 9) {
			num = -1;
		}

		switch (num) {
		case 1: printLine(); printf("Введите номер рейса: ");  inputProtection<int>(routeNumber); break;
		case 2: printLine(); printf("Введите новое направление: "); std::cin >> new_dist;  break;
		case 3: if (routeNumber >= 0 && new_dist[0] != '\0') {
			list_element* flight = list->get_root();
			while (flight->getValue()->getRouteNumber() != routeNumber && flight->getNext() != 0) {
				flight = flight->getNext();
			}
			if (flight->getValue()->getRouteNumber() == routeNumber) {
				flight->getValue()->setDestination(new_dist);
				scanf("%*c");
				return;
			}
			printf("Рейс с таким номером не найден!\n");
			scanf("%*c");
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

void insertNewElement(linked_list* list) {
	int routeNumber = -1;
	int placesLeft = -1;
	int time_hours = -1;
	int time_minutes = -1;
	char* destination = new char[30];
	destination[0] = '\0';
	double price = -1;
	int num = -1;

	do {
		system("CLS");
		if (routeNumber == -1)
			printf("1. Ввести номер рейса\n");
		else
			printf("1. Номер рейса введён (%d)\n", routeNumber);
		if (placesLeft == -1)
			printf("2. Ввести количество свободных мест\n");
		else
			printf("2. Количество свободных мест введено (%d)\n", placesLeft);
		if (time_hours == -1)
			printf("3. Ввести время отправления (часы)\n");
		else
			printf("3. Время отправления (часы) введено (%d)\n", time_hours);
		if (time_minutes == -1)
			printf("4. Ввести время отправления (минуты)\n");
		else
			printf("4. Время отправления (минуты) введено (%d)\n", time_minutes);
		if (destination[0] == '\0')
			printf("5. Ввести направление полета\n");
		else
			printf("5. Направление полета введёно (%s)\n", destination);
		if (price == -1)
			printf("6. Ввести стоимость билета\n");
		else
			printf("6. Стоимость билета введена (%lf)\n", price);
		printf("7. Добавить рейс\n");
		printf("0. Назад\n");
		num = _getch() - '0';
		if (num < 0 || num > 9) {
			num = -1;
		}
		switch (num) {
		case 0: break;
		case 1: printLine(); printf("Введите номер рейса: "); inputProtection<int>(routeNumber); break;
		case 2: printLine(); printf("Введите количество свободных мест: "); inputProtection<int>(placesLeft); break;
		case 3: printLine(); printf("Введите время отправления (часы): "); inputProtection<int>(time_hours); break;
		case 4: printLine(); printf("Введите время отправления (минуты): "); inputProtection<int>(time_minutes); break;
		case 5: printLine(); printf("Введите направление полета: "); std::cin >> destination; break;
		case 6: printLine(); printf("Введите стоимость билета: "); inputProtection<double>(price); break;
		case 7: printLine(); if (routeNumber >= 0 && price > 0 && time_minutes >= 0 && time_minutes < 60 && time_hours >= 0 && time_hours < 24 && placesLeft >= 0 && destination[0] != '\0') {
			list_element* element = list->get_root();
			while (element != 0 && element->getValue()->getRouteNumber() < routeNumber) {
				element = element->getNext();
			}
			Route* data = new Route(routeNumber, destination, time_hours, time_minutes, price, placesLeft);
			if (element == 0) {
				list->insert(data);
				printf("Рейс успешно вставлен!\n");
				system("pause");
				return;
			}
			if (element == list->get_root()) {
				list_element* new_element = new list_element(data);
				list->get_root()->setPrev(new_element);
				new_element->setNext(list->get_root());
				list->set_root(new_element);
				printf("Рейс успешно вставлен!\n");
				system("pause");
				return;
			}
			if (element->getValue()->getRouteNumber() == routeNumber) {
				printf("Рейс с таким номером уже существует!\n");
				system("pause");
				break;
			}
			else
			{
				list_element* new_element = new list_element(data);
				new_element->setNext(element);
				new_element->setPrev(element->getPrev());
				element->getPrev()->setNext(new_element);
				element->setPrev(new_element);
				printf("Рейс успешно вставлен!\n");
				system("pause");
				return;
			}
		}
			  else {
			printf("Введены не все данные!");
			scanf("%*c");
		}
			  break;
		}
	} while (num != 0);
}