#include <iostream>
#include "array_stack.h"
#include "list_stack.h"

int main()
{
    setlocale(LC_CTYPE, "Russian");

    std::cout << "Реализация через список:\n";
    list_stack* lstack = new list_stack();
    lstack->push_back(1);
    lstack->push_back(2);
    lstack->push_back(3);
    for (int i = 0; i < 3; i++) {
        std::cout << lstack->get_root()->getValue() << "\n";
        lstack->pop_back();
    }

    std::cout << "Реализация через массив:\n";
    array_stack* stack = new array_stack();
    stack->push_back(1);
    stack->push_back(2);
    stack->push_back(3);
    for (int i = 0; i < 3; i++) {
        std::cout << stack->back() << "\n";
        stack->pop_back();
    }
}