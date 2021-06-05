#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <queue>

enum class SortMode { RandomSort = 1, StraightSort = 2, ReverseSort = 3 };

void readData(std::string& path, const int number, std::vector<int>& vec);
void bubbleSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void testSort(void (*sortFunc)(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations), const int numbers, std::string& path, SortMode mode);
void shakerSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void quickSortT(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void mergeSortT(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations);
void copyT(std::vector<int>& src, std::vector<int>& dst, const int index, unsigned long long& numberOfActions);

int main()
{
	setlocale(LC_ALL, "Russian");
	std::string path;
	std::cout << "Введите имя файла: ";
	std::cin >> path;

	std::vector <int> sizes = { 10000, 50000, 100000, 150000 };

	for (int i = 0; i < sizes.size(); i++) {
		std::cout << "Количество элементов " << sizes[i] << "\n";
		if (sizes[i] <= 10000) {
			// bubble sort
			std::cout << "Пузырек рандом\n";
			testSort(bubbleSort, sizes[i], path, SortMode::RandomSort);
			std::cout << "Пузырек прямая\n";
			testSort(bubbleSort, sizes[i], path, SortMode::StraightSort);
			std::cout << "Пузырек реверснутая\n";
			testSort(bubbleSort, sizes[i], path, SortMode::ReverseSort);
			std::cout << "-----\n";
		}
		if (sizes[i] <= 20000) {
			// shaker sort
			std::cout << "Шейкер рандом\n";
			testSort(shakerSort, sizes[i], path, SortMode::RandomSort);
			std::cout << "Шейкер прямая\n";
			testSort(shakerSort, sizes[i], path, SortMode::StraightSort);
			std::cout << "Шейкер реверснутая\n";
			testSort(shakerSort, sizes[i], path, SortMode::ReverseSort);
			std::cout << "-----\n";
		}
		// quick sort
		std::cout << "Быстрая рандом\n";
		testSort(quickSortT, sizes[i], path, SortMode::RandomSort);
		std::cout << "Быстрая прямая\n";
		testSort(quickSortT, sizes[i], path, SortMode::StraightSort);
		std::cout << "Быстрая реверснутая\n";
		testSort(quickSortT, sizes[i], path, SortMode::ReverseSort);
		std::cout << "-----\n";
		// merge sort
		std::cout << "Слияния рандом\n";
		testSort(mergeSortT, sizes[i], path, SortMode::RandomSort);
		std::cout << "Слияния прямая\n";
		testSort(mergeSortT, sizes[i], path, SortMode::StraightSort);
		std::cout << "Слияния реверснутая\n";
		testSort(mergeSortT, sizes[i], path, SortMode::ReverseSort);
		std::cout << "-----------------------------------------\n-----------------------------------------\n";
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

void testSort(void (*sortFunc)(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations), const int numbers, std::string& path, SortMode mode) {
	unsigned long long countOfMainOperations = 0;
	unsigned long long countOfOtherOperations = 0;
	unsigned long long timeInMs = 0;
	std::vector<int> vec;
	readData(path, numbers, vec);

	switch (mode) {
	case SortMode::StraightSort:
		std::sort(vec.begin(), vec.end());
		break;
	case SortMode::ReverseSort:
		std::sort(vec.begin(), vec.end(), [](auto& x, auto& y) {
			return x < y;
			});
		break;

	}

	std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();
	sortFunc(0, vec.size(), vec, countOfMainOperations, countOfOtherOperations);
	std::chrono::steady_clock::time_point currTime = std::chrono::high_resolution_clock::now();
	timeInMs = static_cast<unsigned long long>(std::chrono::duration_cast<std::chrono::milliseconds>(currTime - startTime).count());

	for (int i = 0; i < vec.size() - 1; i++) {
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
	int temp = 0;
	countOfOtherOperations++;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < r - 1; j++) {
			if (vec[j] > vec[j + 1]) {
				temp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = temp;
				countOfMainOperations += 3;
			}
			countOfMainOperations++;
			countOfOtherOperations++;
		}
		countOfOtherOperations++;
	}
}

void shakerSort(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations) {
	int control = r - 1;
	countOfMainOperations++;
	int left = 0;
	int right = r - 1;
	countOfMainOperations++;
	int temp = 0;
	countOfOtherOperations += 2;
	do {
		countOfOtherOperations++;
		for (int i = left; i < right; i++) {
			if (vec[i] > vec[i + 1]) {
				temp = vec[i];
				vec[i] = vec[i + 1];
				vec[i + 1] = temp;
				countOfMainOperations += 3;
				control = i;
				countOfOtherOperations++;
			}
			countOfMainOperations++;
			countOfOtherOperations++;
		}
		right = control;
		countOfOtherOperations++;
		for (int i = right; i > left; i--) {
			if (vec[i] < vec[i - 1]) {
				temp = vec[i];
				vec[i] = vec[i - 1];
				vec[i - 1] = temp;
				countOfMainOperations += 3;
				control = i;
				countOfOtherOperations++;
			}
			countOfMainOperations++;
			countOfOtherOperations++;
		}
		left = control;
		countOfOtherOperations++;
	} while (left < right);
}

void quickSortT(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations) {
	int i = l;
	int j = r - 1;
	int temp = 0;
	int centerEl = vec[i + (j - i) / 2];
	countOfMainOperations++;
	countOfOtherOperations += 3;

	while (j >= l && i <= r) {
		countOfOtherOperations++;
		while (vec[i] < centerEl)
		{
			i++;
			countOfOtherOperations++;
			countOfMainOperations++;
		}
		while (vec[j] > centerEl) {
			j--;
			countOfOtherOperations++;
			countOfMainOperations++;
		}
		countOfOtherOperations++;
		if (i <= j) {
			temp = vec[i];
			vec[i] = vec[j];
			vec[j] = temp;
			countOfMainOperations += 3;
			i++;
			j--;
			countOfOtherOperations += 2;
		}
		else {
			if (j > l)
				quickSortT(l, j + 1, vec, countOfMainOperations, countOfOtherOperations);
			countOfOtherOperations++;
			if (i < r)
				quickSortT(i, r, vec, countOfMainOperations, countOfOtherOperations);
			countOfOtherOperations++;
			return;
		}
	};
};

void mergeSortT(const int l, const int r, std::vector<int>& vec, unsigned long long& countOfMainOperations, unsigned long long& countOfOtherOperations) {
	if (r - l <= 1) {
		countOfOtherOperations++;
		return;
	}

	int temp = 0;
	countOfOtherOperations++;

	int middle = l + (r - l) / 2;
	countOfOtherOperations += 2;

	mergeSortT(l, middle, vec, countOfMainOperations, countOfOtherOperations);
	mergeSortT(middle, r, vec, countOfMainOperations, countOfOtherOperations);

	int i = l;
	int j = middle;
	countOfOtherOperations += 2;

	std::vector<int> tempArray;

	while (i < middle && j < r) {
		countOfOtherOperations++;
		if (vec[i] < vec[j])
		{
			tempArray.push_back(vec[i]);
			countOfMainOperations++;
			i++;
			countOfOtherOperations++;
		}
		else
		{
			tempArray.push_back(vec[j]);
			countOfMainOperations++;
			j++;
			countOfOtherOperations++;
		}
		countOfMainOperations++;

		countOfOtherOperations++;
		if (i == middle) {
			while (j < r) {
				tempArray.push_back(vec[j]);
				countOfMainOperations++;
				j++;
				countOfOtherOperations++;
			}
			copyT(tempArray, vec, l, countOfMainOperations);
			return;
		}
		countOfOtherOperations++;
		if (j == r) {
			while (i < middle) {
				tempArray.push_back(vec[i]);
				countOfMainOperations++;
				i++;
				countOfOtherOperations++;
			}
			copyT(tempArray, vec, l, countOfMainOperations);
			return;
		}
	}
}

void copyT(std::vector<int>& src, std::vector<int>& dst, const int index, unsigned long long& numberOfActions) {
	for (int i = 0; i < src.size(); i++) {
		dst[index + i] = src[i];
		numberOfActions += 2;
	}
}