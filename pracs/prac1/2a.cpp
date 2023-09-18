#include <iostream>
#include <vector>

// Функция для сортировки чисел с использованием битового массива
void sortWithBitArray(unsigned char bitArray, std::vector<int>& sortedNumbers) {
    sortedNumbers.clear(); // Очищаем вектор от предыдущих значений
    for (int i = 0; i <= 7; ++i) {
        if (bitArray & (1 << i)) { // Проверяем, установлен ли i-й бит в битовом массиве
            sortedNumbers.push_back(i); // Если бит установлен, добавляем число i в отсортированный вектор
        }
    }
}

int main() {
    std::vector<int> numbers; // Вектор для хранения введенных чисел
    std::cout << "Введите не более 8 чисел (от 0 до 7): ";

    for (int i = 0; i < 8; ++i) {
        int num;
        std::cin >> num;
        if (num < 0 || num > 7) {
            std::cerr << "Число вне диапазона (0-7). Пожалуйста, введите правильное число." << std::endl;
            return 1;
        }
        numbers.push_back(num); // Добавляем числа в вектор
    }

    unsigned char bitArray = 0; // Инициализируем битовый массив нулем

    // Устанавливаем биты в битовом массиве в соответствии с введенными числами
    for (int num : numbers) {
        bitArray |= (1 << num);
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
