#include <iostream>
#include <vector>

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
    int count;
    std::cout << "Введите размер массива (не больше 64): ";
    std::cin >> count;

    std::vector<int> numbers; // Вектор для хранения введенных чисел
    std::cout << "Введите массив (от 0 до 63): ";

    for (int i = 0; i < count; ++i) {
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
