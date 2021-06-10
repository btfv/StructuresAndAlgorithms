#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include "ITree.h"
#include "SplayTree.h"
#include "AvlTree.h"

void readDataToTree(std::string& path, const int number, ITree<unsigned long>& tree);
void readDataToVector(std::string& path, const int number, std::vector<unsigned long>& vec);
void searchInTree(unsigned long& key, ITree<unsigned long>& tree);
void testTree(ITree<unsigned long>& tree, std::vector<unsigned long>& vec);

int main()
{
	/*srand(time(nullptr));
	setlocale(LC_ALL, "Russian");
	std::string path;
	std::cout << "Введите имя файла: ";
	std::cin >> path;
	
	std::vector<unsigned long> vec;
	readDataToVector(path, 50000, vec);
	
	std::cout << "Splay Tree:\n";
	SplayTree<unsigned long> splayTree;
	readDataToTree(path, 10000, splayTree);
	testTree(splayTree, vec);

	std::cout << "-------------------------------------------------\n-------------------------------------------------\n";

	std::cout << "AVL Tree:\n";
	AvlTree<unsigned long> avlTree;
	readDataToTree(path, 10000, avlTree);
	testTree(avlTree, vec);*/

	AvlTree<unsigned long> avlTree;
	avlTree.Insert(10);
	avlTree.Insert(11);
	avlTree.Insert(12);
	std::cout << avlTree.Search(10) << "\n";
	std::cout << avlTree.Search(11) << "\n";
	std::cout << avlTree.Search(12) << "\n";
	return EXIT_SUCCESS;
}

void testTree(ITree<unsigned long>& tree, std::vector<unsigned long>& vec) {
	unsigned long searchKeys[3];
	unsigned long maxKey = pow(10, 8);
	for (int i = 0; i < 100; i++) {
		searchKeys[0] = maxKey + rand() % maxKey;
		searchKeys[1] = vec[rand() % vec.size()];
		searchKeys[2] = rand() % maxKey;

		for (int j = 0; j < 3; j++) {
			std::cout << i * 3 + j << ". ";
			searchInTree(searchKeys[j], tree);
			std::cout << "\n";
		}
	}
}

void readDataToTree(std::string& path, const int number, ITree<unsigned long>& tree) {
	std::fstream ifs(path, std::ios_base::in);
	if (!ifs.is_open()) {
		std::cout << "Файл не открылся";
		exit(EXIT_FAILURE);
	}
	int temp;
	for (int i = 0; i < number; i++) {
		ifs >> temp;
		tree.Insert(temp);
	}
}

void readDataToVector(std::string& path, const int number, std::vector<unsigned long>& vec) {
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

void searchInTree(unsigned long& key, ITree<unsigned long>& tree) {
	if (tree.Search(key)) {
		std::cout << "Найден";
	}
	else {
		std::cout << "Не найден";
	}
}