#include <iostream>
#include <vector>
//32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
// Функция для сортировки чисел с использованием битового массива
void sortWithBitArray(unsigned long long bitArray, std::vector<int>& sortedNumbers) {
    sortedNumbers.clear(); // Очищаем вектор от предыдущих значений
    for (int i = 0; i <= 63; ++i) {
        if (bitArray & (1ULL << i)) { // Проверяем, установлен ли i-й бит в битовом массиве,мы используем 1ULL (unsigned long long literal) для явного указания на беззнаковый long long
            sortedNumbers.push_back(i); // Если бит установлен, добавляем число i в отсортированный вектор
        }
    }
}

int main() {
    std::vector<int> numbers; // Вектор для хранения введенных чисел
    std::cout << "Введите не более 64 чисел (от 0 до 63): ";

    for (int i = 0; i < 64; ++i) {
        int num;
        std::cin >> num;
        if (num < 0 || num > 63) {
            std::cerr << "Число вне диапазона (0-63). Пожалуйста, введите правильное число." << std::endl;
            return 1;
        }
        numbers.push_back(num); // Добавляем числа в вектор
    }

    unsigned long long bitArray = 0; // Инициализируем битовый массив нулем

    // Устанавливаем биты в битовом массиве в соответствии с введенными числами
    for (int num : numbers) {
        bitArray |= (1ULL << num);
    }

    std::vector<int> sortedNumbers; // Вектор для отсортированных чисел
    sortWithBitArray(bitArray, sortedNumbers); // Вызываем функцию сортировки

    std::cout << "Отсортированный набор чисел: ";
    for (int num : sortedNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}