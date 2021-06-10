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
void mergeSortRec(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void copyT(std::vector<int>& src, std::vector<int>& dst, const int index, unsigned long long& numberOfActions);
void mergeSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void quickSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);

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
	for (int i = 0; (++countOfOtherOperations) && i < r-1; i++) {
		for (int j = 0; (++countOfOtherOperations) && j < r - 1-i; j++) {
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
	mergeSortRec(l, r, vec, countOfMainOperations, countOfOtherOperations);
}


void mergeSortRec(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations) {
	if ((++countOfOtherOperations) && r - l <= 1) {
		return;
	}

	int temp = 0;

	int middle = l + (r - l) / 2;

	mergeSortRec(l, middle, vec, countOfMainOperations, countOfOtherOperations);
	mergeSortRec(middle, r, vec, countOfMainOperations, countOfOtherOperations);

	int i = l;
	int j = middle;

	std::vector<int> tempArray;

	while ((++countOfOtherOperations) && i < middle && (++countOfOtherOperations) && j < r) {
		if ((++countOfMainOperations) && vec[i] < vec[j])
		{
			tempArray.push_back(vec[i]);
			i++;
		}
		else
		{
			tempArray.push_back(vec[j]);
			j++;
		}

		if ((++countOfOtherOperations) && i == middle) {
			while ((++countOfOtherOperations) && j < r) {
				tempArray.push_back(vec[j]);
				j++;
			}
			copyT(tempArray, vec, l, countOfOtherOperations);
			return;
		}
		if ((++countOfOtherOperations) && j == r) {
			while ((++countOfOtherOperations) && i < middle) {
				tempArray.push_back(vec[i]);
				i++;
			}
			copyT(tempArray, vec, l, countOfOtherOperations);
			return;
		}
	}
}

void copyT(std::vector<int>& src, std::vector<int>& dst, const int index, unsigned long long& numberOfActions) {
	for (int i = 0; ++numberOfActions && i < src.size(); i++) {
		dst[index + i] = src[i];
	}
}