#include <iostream>
#include <string>
#include "array_stack.h"

int main()
{
    setlocale(LC_CTYPE, "Russian");

    std::cout << "Реализация через массив:\n";
    array_stack<int> stack;
    std::string s;
    std::cin >> s;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '[') {
            stack.push_back((int)'[');
        }
        else if (s[i] == ']') {
            if (stack.back() != (int)'[') {
                std::cout << "Строка составлена неправильно!\n";
                return 0;
            }
            stack.pop_back();
        }

        if (s[i] == '<') {
            stack.push_back((int)'<');
        }
        else if (s[i] == '>') {
            if (stack.back() != (int)'<') {
                std::cout << "Строка составлена неправильно!\n";
                return 0;
            }
            stack.pop_back();
        }

        if (s[i] == '(') {
            stack.push_back((int)'(');
        }
        else if (s[i] == ')') {
            if (stack.back() != (int)'(') {
                std::cout << "Строка составлена неправильно!\n";
                return 0;
            }
            stack.pop_back();
        }
    }
    if (!stack.is_empty()) {
        std::cout << "Строка составлена неправильно!\n";
        return 0;
    }
    std::cout << "Строка составлена правильно!\n";
    
    return 0;
}