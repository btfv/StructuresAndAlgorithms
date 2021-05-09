#include <iostream>
#include "linked_list.h"
#include "custom_array.h"
#include <fstream>
#include <string>

void matrixImplementation(int&, int&, custom_array<custom_array<int>>&);
void readData(std::string&);
void dfs_matrix(int, const int, custom_array<bool>&, custom_array<custom_array<int>>&);
void dfs_list(int, custom_array<bool>&, custom_array<custom_array<int>>&);
void listImplementation(int&, int&, custom_array<custom_array<int>>&);

int main(int argc, char* argv[]) {
    /*
    * Структура файла:
    * Первая строчка - количество вершин в графе
    * Вторая - матрица смежности
    * Третья - номер вершины, от которой необходимо найти недостижимые
    */
    setlocale(LC_ALL, "Rus");
    std::string path;
    if (argc > 1) {
        path = argv[1];
    }
    else {
        std::cout << "Введите имя текстового файла: ";
        std::cin >> path;
    }
    system("CLS");
    readData(path);
    return 0;
}

void dfs_matrix(int num, const int size, custom_array<bool>& used, custom_array<custom_array<int>>& matrix) {
    // Ищем все вершины графа, достижимые от изначальной вершины num через поиск в глубину
    used[num] = true;
    for (int j = 0; j < size; j++) {
        if (matrix[num][j] && !used[j]) {
            dfs_matrix(j, size, used, matrix);
        }
    }
}

void dfs_list(int num, custom_array<bool>& used, custom_array<custom_array<int>>& list) {
    // Ищем все вершины графа, достижимые от изначальной вершины num через поиск в глубину
    used[num] = true;
    for (int j = 0; j < list[num].get_length(); j++) {
        if(!used[list[num][j]])
            dfs_list(list[num][j], used, list);
    }
}

void readData(std::string& path) {
    std::ifstream ifs(path, std::ios_base::in);
    if (!ifs.is_open()) {
        std::cout << "Файл не найден!\n";
        return;
    }
    int num_of_vertexs;
    ifs >> num_of_vertexs;

    custom_array<custom_array<int>> matrix(num_of_vertexs, custom_array<int>(num_of_vertexs));
    // Матрица смежности
    custom_array<custom_array<int>> adjacencyList(num_of_vertexs);
    // Список смежности

    for (int i = 0; i < num_of_vertexs; i++) {
        for (int j = 0; j < num_of_vertexs; j++) {
            ifs >> matrix[i][j];
            if (matrix[i][j]) {
                adjacencyList[i].push_back(j);
            }
        }
    }

    int vertex_num;
    ifs >> vertex_num;
    vertex_num--;

    matrixImplementation(vertex_num, num_of_vertexs, matrix);
    std::cout << "\n---\n";
    listImplementation(vertex_num, num_of_vertexs, adjacencyList);

    ifs.close();
}

void matrixImplementation(int& vertex_num, int& num_of_vertexs, custom_array<custom_array<int>>& matrix) {
    std::cout << "Реализация через матрицу:\n";
    custom_array<bool> used(num_of_vertexs);
    // used - массив, отвечающий за достижимость iтой вершины от вершины vertex_num
    for (int i = 0; i < num_of_vertexs; i++) {
        used[i] = false;
    }

    dfs_matrix(vertex_num, num_of_vertexs, used, matrix);

    std::cout << "Недостижимые вершины:\n";
    for (int i = 0; i < used.get_length(); i++) {
        if (!used[i]) {
            std::cout << i + 1 << ' ';
        }
    }
    return;
}

void listImplementation(int& vertex_num, int& num_of_vertexs, custom_array<custom_array<int>>& adjacencyList) {
    std::cout << "Реализация через списки:\n";
    custom_array<bool> used(num_of_vertexs);
    // used - массив, отвечающий за достижимость iтой вершины от вершины vertex_num
    for (int i = 0; i < num_of_vertexs; i++) {
        used[i] = false;
    }

    dfs_list(vertex_num, used, adjacencyList);

    std::cout << "Недостижимые вершины:\n";
    for (int i = 0; i < used.get_length(); i++) {
        if (!used[i]) {
            std::cout << i + 1 << ' ';
        }
    }
    return;
}