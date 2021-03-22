#include <iostream>
#include <string>
#include "array_stack.h"
#include "list_stack.h"

int main()
{
    setlocale(LC_CTYPE, "Russian");
    
    std::cout << "Реализация через массив:\n";
    array_stack<int> array_stack;
    std::string s;
    std::cin >> s;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '[') {
            array_stack.push_back((int)'[');
        }
        else if (s[i] == ']') {
            if (array_stack.back() != (int)'[') {
                std::cout << "Строка составлена неправильно!\n";
                return 0;
            }
            array_stack.pop_back();
        }

        if (s[i] == '<') {
            array_stack.push_back((int)'<');
        }
        else if (s[i] == '>') {
            if (array_stack.back() != (int)'<') {
                std::cout << "Строка составлена неправильно!\n";
                return 0;
            }
            array_stack.pop_back();
        }

        if (s[i] == '(') {
            array_stack.push_back((int)'(');
        }
        else if (s[i] == ')') {
            if (array_stack.back() != (int)'(') {
                std::cout << "Строка составлена неправильно!\n";
                return 0;
            }
            array_stack.pop_back();
        }
    }
    if (!array_stack.is_empty()) {
        std::cout << "Строка составлена неправильно!\n";
        return 0;
    }
    std::cout << "Строка составлена правильно!\n";
    
    std::cout << "Реализация через список:\n";
    list_stack<int> list_stack;
    std::cin >> s;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '[') {
            list_stack.push_back((int)'[');
        }
        else if (s[i] == ']') {
            if (list_stack.back() != (int)'[') {
                std::cout << "Строка составлена неправильно!\n";
                return 0;
            }
            list_stack.pop_back();
        }

        if (s[i] == '<') {
            list_stack.push_back((int)'<');
        }
        else if (s[i] == '>') {
            if (list_stack.back() != (int)'<') {
                std::cout << "Строка составлена неправильно!\n";
                return 0;
            }
            list_stack.pop_back();
        }

        if (s[i] == '(') {
            list_stack.push_back((int)'(');
        }
        else if (s[i] == ')') {
            if (list_stack.back() != (int)'(') {
                std::cout << "Строка составлена неправильно!\n";
                return 0;
            }
            list_stack.pop_back();
        }
    }
    if (!list_stack.is_empty()) {
        std::cout << "Строка составлена неправильно!\n";
        return 0;
    }
    std::cout << "Строка составлена правильно!\n";

    return 0;
}
