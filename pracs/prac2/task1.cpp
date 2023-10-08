#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <utility>

// Массив названий улиц
const auto STREETS = {"Центральная", "Молодежная", "Школьная", "Лесная", "Садовая",
                      "Советская", "Новая", "Набережная", "Заречная", "Зеленая"};

std::random_device rd;            // Создаем объект для генерации случайных чисел из аппаратного источника
std::mt19937 gen(rd());       // Инициализируем генератор случайных чисел с помощью аппаратного источника

// Функция для генерации случайного целого числа в заданном диапазоне
int random(int start, int end) {
    std::uniform_int_distribution<> distr(start, end); // Определяем диапазон
    return distr(gen);                                    // Генерируем случайное число
}

// Перегруженная версия функции random, генерирующая случайное число от 0 до end
int random(int end) {
    return random(0, end);
}

// Функция для выбора случайного элемента из контейнера
template <typename Iterator>
Iterator random_choice(Iterator begin, Iterator end) {
    auto len = std::distance(begin, end);     // Вычисляем количество элементов в диапазоне
    std::advance(begin, random(len - 1));              // Смещаем указатель на случайное количество элементов
    return begin;                                      // Возвращаем указатель на случайный элемент
}

// Функция для генерации случайного номера телефона
std::string random_phone_number() {
    std::stringstream number_stream;
    number_stream << 7;                                // Номер всегда начинается с "7"

    for (int i = 0; i < 10; i++) {
        number_stream << random(9);               // Генерируем 10 случайных цифр для номера
    }

    return number_stream.str();                        // Возвращаем сгенерированный номер как строку
}

int main() {
    // Запрашиваем имя файла для записи
    std::string output;
    int n;
    std::cout << "Output file: ";
    std::cin >> output;

    // Запрашиваем количество записей для создания
    std::cout << "Number: ";
    std::cin >> n;

    // Открываем файл для записи в бинарном режиме
    std::ofstream file(output, std::ios::out | std::ios::binary);

    // Проверяем, удалось ли открыть файл
    if (!file.is_open()) {
        std::cout << "Can't write to the file" << std::endl;
        return 1;
    }

    // Генерируем и записываем указанное количество записей
    for (int i = 0; i < n; i++) {
        std::string number = random_phone_number();  // Генерируем случайный номер телефона

        // Генерируем случайный адрес, состоящий из улицы и номера
        std::string address = "ул. " + std::string(*random_choice(STREETS.begin(), STREETS.end())) + " " +
                              std::to_string(random(1, 100));

        // Записываем номер телефона и адрес в файл
        file.write(number.c_str(), number.size() + 1);
        file.write(address.c_str(), address.size() + 1);
    }

    // Закрываем файл
    file.close();

    std::cout << "Records successfully generated and saved to " << output << "." << std::endl;

    return 0; // Завершаем программу
}