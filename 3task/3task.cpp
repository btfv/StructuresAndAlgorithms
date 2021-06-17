#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <queue>

void readData(std::string& path, const int number, std::vector<int>& vec);
void bubbleSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void testSort(void (*sortFunc)(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations), unsigned long long numbers, std::vector<int>& vec);
void shakerSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void quickSortRec(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void mergeSortRec(std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void mergeSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void quickSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void merge(std::vector<int>& dst, std::vector<int>& src, const int pos1, const int pos2, const int pos3, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void copyU(int beginSrc, int endSrc, int beginDest, std::vector<int>& src, std::vector<int>& dst, unsigned long long& numberOfOperations);

int main()
{
	setlocale(LC_ALL, "Russian");
	std::string path;
	std::cout << "Введите имя файла: ";
	std::cin >> path;
	std::cout << "Количество сравнений\n";
	std::vector <int> sizes = { 10000, 50000, 100000, 150000 };

	std::vector <void (*)(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations)> functions = { bubbleSort, shakerSort, quickSort, mergeSort };

	std::vector <int> originalArray;
	readData(path, sizes.back(), originalArray);


	for (int i = 0; i < sizes.size(); i++) {
		std::cout << "Количество элементов " << sizes[i] << "\n";
		for (int j = 0; j < functions.size(); j++) {
			std::vector <int> arrayFromFile(originalArray);
			testSort(functions[j], sizes[i], arrayFromFile);
			std::cout << "-------------------------------------------\n";
			testSort(functions[j], sizes[i], arrayFromFile);
			std::cout << "-------------------------------------------\n";
			std::reverse(arrayFromFile.begin(), arrayFromFile.end());
			testSort(functions[j], sizes[i], arrayFromFile);
			std::cout << "-------------------------------------------\n";
		}
		std::cout << "-------------------------------------------\n-------------------------------------------\n";
	}

	return EXIT_SUCCESS;
}

void readData(std::string& path, const int number, std::vector<int>& vec) {
	std::fstream ifs(path, std::ios_base::in);
	if (!ifs.is_open()) {
		std::cout << "Файл не открылся";
		exit(EXIT_FAILURE);
	}
	int temp;
	for (int i = 0; i < number; i++) {
		ifs >> temp;
		vec.push_back(temp);
	}
}

void testSort(void (*sortFunc)(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations), unsigned long long numbers, std::vector<int>& vec) {
	unsigned long long countOfMainOperations = 0;
	unsigned long long countOfOtherOperations = 0;
	unsigned long long timeInMs = 0;

	std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();
	sortFunc(0, numbers, vec, countOfMainOperations, countOfOtherOperations);
	std::chrono::steady_clock::time_point currTime = std::chrono::high_resolution_clock::now();
	timeInMs = static_cast<unsigned long long>(std::chrono::duration_cast<std::chrono::milliseconds>(currTime - startTime).count());

	for (int i = 0; i < numbers - 1; i++) {
		if (vec[i] > vec[i + 1]) {
			std::cout << vec[i + 1];
			std::cout << "!!! bad sort !!!" << "\n";
			exit(EXIT_FAILURE);
		}
	}

	std::cout << "Время " << timeInMs << " мс\n";
	std::cout << "Количество основных операций " << countOfMainOperations << "\n";
	std::cout << "Количество дополнительных операций " << countOfOtherOperations << "\n";
}

void bubbleSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations) {
	std::cout << "Сортировка пузырьком\n";
	int temp = 0;
	for (int i = 0; (++countOfOtherOperations) && i < r - 1; i++) {
		for (int j = 0; (++countOfOtherOperations) && j < r - 1 - i; j++) {
			if ((++countOfMainOperations) && vec[j] > vec[j + 1]) {
				temp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = temp;
			}
		}
	}
}

void shakerSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations) {
	std::cout << "Сортировка шейкером\n";
	int control = l;
	int left = l;
	int right = r - 1;
	int temp = 0;
	do {
		for (int i = left; (++countOfOtherOperations) && i < right; i++) {
			if ((++countOfMainOperations) && vec[i] > vec[i + 1]) {
				temp = vec[i];
				vec[i] = vec[i + 1];
				vec[i + 1] = temp;
				control = i;
			}
		}
		right = control;
		for (int i = right; (++countOfOtherOperations) && i > left; i--) {
			if ((++countOfMainOperations) && vec[i] < vec[i - 1]) {
				temp = vec[i];
				vec[i] = vec[i - 1];
				vec[i - 1] = temp;
				control = i;
			}
		}
		left = control;
	} while ((++countOfOtherOperations) && left < right);
}

void quickSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations) {
	std::cout << "Быстрая сортировка\n";
	quickSortRec(l, r, vec, countOfMainOperations, countOfOtherOperations);
};


void quickSortRec(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations) {
	int i = l;
	int j = r - 1;
	int temp = 0;
	int centerEl = vec[i + (j - i) / 2];

	while ((++countOfOtherOperations) && j >= l && (++countOfOtherOperations) && i <= r) {
		while ((++countOfMainOperations) && vec[i] < centerEl)
		{
			i++;
		}
		while ((++countOfMainOperations) && vec[j] > centerEl) {
			j--;
		}
		if ((++countOfOtherOperations) && i <= j) {
			temp = vec[i];
			vec[i] = vec[j];
			vec[j] = temp;
			i++;
			j--;
		}
		else {
			if ((++countOfOtherOperations) && j > l)
				quickSortRec(l, j + 1, vec, countOfMainOperations, countOfOtherOperations);
			if ((++countOfOtherOperations) && i < r)
				quickSortRec(i, r, vec, countOfMainOperations, countOfOtherOperations);
			return;
		}
	};
};

void mergeSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations) {
	std::cout << "Сортировка слиянием\n";
	mergeSortRec(vec, countOfMainOperations, countOfOtherOperations);
}


void mergeSortRec(std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations) {
	int i = 0;
	std::vector<int> temp(vec.size());
	int p1 = 0, p2 = 0, p3 = 0;
	bool sorted = 0;
	while ((++countOfOtherOperations) && !sorted) {
		while (++countOfOtherOperations && !sorted && (++countOfMainOperations) && i < vec.size()) {
			p1 = i;
			while ((++countOfOtherOperations) && i < vec.size() - 1 && (++countOfMainOperations) && vec[i] <= vec[i + 1]) i++;
			p2 = ++i;
			if ((++countOfOtherOperations) && p1 == 0 && (++countOfMainOperations) && i >= vec.size()) {
				sorted = 1;
				break;
			}
			while (++countOfMainOperations && i < vec.size() - 1 && (++countOfMainOperations) && vec[i] <= vec[i + 1]) i++;
			p3 = ++i;
			if ((++countOfMainOperations) && p3 > vec.size()) {
				break;
			}
			merge(temp, vec, p1, p2, p3, countOfMainOperations, countOfOtherOperations);
			copyU(p1, p3, p1, temp, vec, countOfMainOperations);
			if ((++countOfOtherOperations) && p1 == 0 && (++countOfMainOperations) && p3 >= vec.size()) {
				sorted = 1;
				break;
			}
		}
		i = 0;
		p1 = 0;
		p2 = 0;
		p3 = 0;
	}
	return;
}

void merge(std::vector<int>& dst, std::vector<int>& src, const int pos1, const int pos2, const int pos3, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations) {
	int i = pos1;
	int j = pos2;
	while (((++countOfOtherOperations) && i < pos2) || ((++countOfOtherOperations) && j < pos3)) {
		if ((++countOfOtherOperations) && i < pos2 && (++countOfOtherOperations) && j < pos3) {
			if ((++countOfMainOperations) && src[i] <= src[j]) {
				dst[i + j - pos2] = src[i];
				i++;
			}
			else {
				dst[i + j - pos2] = src[j];
				j++;
			}
		}
		else if ((++countOfOtherOperations) && i < pos2) {
			dst[i + j - pos2] = src[i];
			i++;
		}
		else if ((++countOfOtherOperations) && j < pos3) {
			dst[i + j - pos2] = src[j];
			j++;
		}
	}
}

void copyU(int beginSrc, int endSrc, int beginDest, std::vector<int>& src, std::vector<int>& dst, unsigned long long& numberOfOperations) {
	for (int i = beginSrc; (++numberOfOperations) && i < endSrc; i++) {
		dst[beginDest + i - beginSrc] = src[i];
	}
}