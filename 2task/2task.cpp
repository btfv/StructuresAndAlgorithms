#include <iostream>
#include "linked_list.h"
#include "custom_array.h"
#include <vector>
#define ARRAY_SIZE 100

void scan_matrix(custom_array<custom_array<int>>&);

int main() {
    setlocale(LC_ALL, "Rus");
    //std::vector <std::vector <int>> x(10, std::vector<int>(10));
    custom_array<custom_array<int>> arr(ARRAY_SIZE, custom_array<int>(ARRAY_SIZE));
    
    return 0;
}