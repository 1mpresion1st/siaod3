#include <iostream>
#include <vector>
//32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31

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
