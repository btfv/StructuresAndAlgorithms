#include <iostream>
#include "linked_list.h"
#include "custom_array.h"
#include <fstream>
#include <string>
#define ARRAY_SIZE 100

bool* scan_matrix(custom_array<custom_array<int>>&);
void solve(std::string&);
void dfs_matrix(int, const int, custom_array<bool>&, custom_array<custom_array<int>>&);

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");
    std::string path;
    if (argc > 1) {
        path = argv[1];
    }
    else {
        std::cout << "Введите имя файла: ";
        std::cin >> path;
    }
    system("CLS");
    solve(path);
    return 0;
}

void dfs_matrix(int num, const int size, custom_array<bool>& used, custom_array<custom_array<int>>& matrix) {
    used[num] = true;
    for (int j = 0; j < size; j++) {
        if (matrix[num][j] && !used[j]) {
            dfs_matrix(j, size, used, matrix);
        }
    }
}

void solve(std::string& path) {
    std::ifstream ifs(path, std::ios_base::in);
    /*std::cout << "Нумерация вершин с 1!\n";
    std::cout << "Введите количество вершин\n";*/
    int num_of_vertexs;
    ifs >> num_of_vertexs;

    custom_array<custom_array<int>> matrix(num_of_vertexs, custom_array<int>(num_of_vertexs));
    custom_array<int> component;

    custom_array<bool> used(num_of_vertexs);
    
    for (int i = 0; i < num_of_vertexs; i++) {
        used[i] = false;
    }
    //std::cout << "Введите матрицу смежности\n";
    for (int i = 0; i < num_of_vertexs; i++) {
        for (int j = 0; j < num_of_vertexs; j++) {
            ifs >> matrix[i][j];
        }
    }

    //std::cout << "Введите номер вершины, от которой требуется найти недостижимые\n";
    int vertex_num;
    ifs >> vertex_num;
    vertex_num--;

    dfs_matrix(vertex_num, num_of_vertexs, used, matrix);

    std::cout << "Недостижимые вершины:\n";
    for (int i = 0; i < used.get_length(); i++) {
        if (!used[i]) {
            std::cout << i + 1 << ' ';
        }
    }
    ifs.close();
    return;
}