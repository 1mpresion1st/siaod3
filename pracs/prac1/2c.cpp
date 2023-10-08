#include <iostream>
#include <vector>

// Функция для сортировки чисел с использованием битового массива
void sortWithBitArray(const std::vector<unsigned char>& bitArray, std::vector<int>& sortedNumbers) {
    sortedNumbers.clear(); // Очищаем вектор от предыдущих значений
    for (int i = 0; i < bitArray.size(); ++i) {
        for (int j = 0; j < 8; ++j) {
            if (bitArray[i] & (1 << j)) { // Проверяем, установлен ли j-й бит в i-м элементе битового массива
                sortedNumbers.push_back(i * 8 + j); // Если бит установлен, добавляем число в отсортированный вектор
            }
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

    // Вычисляем количество элементов в массиве беззнаковых символов, необходимое для хранения 64 чисел
    const int arraySize = (64 + 7) / 8; // 8 битов на байт

    std::vector<unsigned char> bitArray(arraySize, 0); // Инициализируем массив беззнаковых символов нулями

    // Устанавливаем биты в битовом массиве в соответствии с введенными числами
    for (int num : numbers) {
        int byteIndex = num / 8;
        int bitIndex = num % 8;
        bitArray[byteIndex] |= (1 << bitIndex);
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
