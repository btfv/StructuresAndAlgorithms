#include <iostream>

/* Класс "Рациональное число" (РЧ). Поля: числитель, знаменатель. Методы: вычисление модуля,
перегрузка операции приведения типа к double, операций вычитания "-" из РЧ целого числа и РЧ,
операции получения обратного РЧ "!". */

class RationalNumber {
private:
    int numerator; // числитель
    int denominator; // знаменатель (>= 1)
public:
    explicit RationalNumber(const int& numerator1 = 0, const int& denominator1 = 1) : numerator(numerator1), denominator(denominator1) {
        std::cout << "Конструктор c параметрами." << std::endl;
    }

    RationalNumber(const RationalNumber& object) : numerator(object.numerator), denominator(object.denominator) {
        std::cout << "Конструктор копирования." << std::endl;
    }

    ~RationalNumber() {
        std::cout << "Деструктор." << std::endl;
    }

    double module() const { // вычисление модуля
        std::cout << "Взятие модуля." << std::endl;
        double temp = (double)numerator / denominator;
        return  temp > 0 ? temp : -temp;
    }

    void setNumerator(const int& numerator1) {
        std::cout << "Сеттер числителя." << std::endl;
        numerator = numerator1;
    }

    void setDenominator(const int& denominator1) {
        std::cout << "Сеттер знаменателя." << std::endl;
        denominator = denominator1;
    }

    int getNumerator() const {
        std::cout << "Геттер числителя." << std::endl;
        return numerator;
    }

    int getDenominator() const {
        std::cout << "Геттер знаменателя." << std::endl;
        return denominator;
    }

    explicit operator double() const { // приведение типа к double
        std::cout << "Приведение рационального числа к типу double." << std::endl;
        return (double)numerator / denominator;
    }

    RationalNumber operator-(const int& a) const // операция вычитания из РЧ целого числа
    {
        std::cout << "Вычитание из РЧ целого числа." << std::endl;
        return RationalNumber(numerator - a * denominator, denominator);
    }

    RationalNumber operator-(const RationalNumber& obj) const { // операция вычитания из РЧ РЧ
        std::cout << "Вычитания из РЧ РЧ." << std::endl;
        if (denominator == obj.denominator)
            return RationalNumber(numerator - obj.numerator, denominator);
        else
            return RationalNumber(numerator * obj.denominator - obj.numerator * denominator, denominator * obj.denominator);
    }

    RationalNumber operator! () const { // операция получения обратного РЧ
        return RationalNumber(denominator, numerator);
    }

    friend std::ostream& operator<<(std::ostream& out, const RationalNumber& RationalNumber);
    friend std::istream& operator>>(std::istream& in, RationalNumber& RationalNumber);

};

std::ostream& operator<<(std::ostream& out, const RationalNumber& RationalNumber) {
    out << "Перегрузка операции вывода." << std::endl;
    out << "Числитель: " << RationalNumber.numerator << "\nЗнаменатель: " << RationalNumber.denominator << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, RationalNumber& RationalNumber) {
    std::cout << "Перегрузка операции ввода." << std::endl;
    std::cout << "Введите числитель: ";
    in >> RationalNumber.numerator;
    std::cout << "Введите знаменатель: ";
    in >> RationalNumber.denominator;
    std::cout << "\n";
    return in;
}

int main() {

    setlocale(LC_ALL, "Rus");

    int choice, stillWork = 1, NumSecond, new_Num, new_Denum, integer_number;

    RationalNumber* number = new RationalNumber; // выделяю память под число
    RationalNumber* number2 = new RationalNumber; // выделяю память под второе число

    do {
        system("CLS");
        std::cout << "\n1. Введение рационального числа." << std::endl;
        std::cout << "2. Изменить числитель." << std::endl;
        std::cout << "3. Изменить знаменатель." << std::endl;
        std::cout << "4. Операция приведения типа к double." << std::endl;
        std::cout << "5. Операция вычитания '-' из РЧ целого числа." << std::endl;
        std::cout << "6. Операция вычитания '-' из РЧ РЧ." << std::endl;
        std::cout << "7. Операция получения обратного РЧ '!'." << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "\nВведите пункт меню: ";

        std::cin >> choice;
        system("CLS");
        std::cout << *number;
        switch (choice) {
        case 0:
            stillWork = 0;
            delete number;
            delete number2;
            std::cout << "Успешно завершено." << std::endl;
            break;
        case 1:
            std::cin >> *number;
            break;
        case 2:
            std::cout << "Введите новый числитель: ";
            std::cin >> new_Num;
            number->setNumerator(new_Num);
            break;
        case 3:
            std::cout << "Введите новый знаменатель: ";
            std::cin >> new_Denum;
            number->setDenominator(new_Denum);
            break;
        case 4:
            break;
        case 5:
            std::cout << "Введите целое число, которое нужно вычесть: ";
            std::cin >> integer_number;
            std::cout << *number - integer_number;
            break;
        case 6:
            std::cout << "Введите рациональное число, которое нужно вычесть: ";
            std::cin >> *number2;
            std::cout << *number - *number2;
            break;
        case 7:
            break;
        default: std::cout << "Некорректный ввод";

        }
        system("pause");
    } while (stillWork);

    return 0;
}

