#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Функция для выполнения бинарного поиска в таблице смещений
std::ios::pos_type find(std::vector<std::pair<long, std::ios::pos_type>> &offset_table, long key) {
    int l = 0;
    int r = offset_table.size();

    // Бинарный поиск в отсортированной таблице
    while (l <= r) {
        int m = l + (r - l) / 2;

        if (offset_table[m].first == key)
            return offset_table[m].second; // Если ключ найден, возвращаем позицию в файле

        if (offset_table[m].first < key)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1; // Если ключ не найден, возвращаем -1
}

// Функция для чтения строки из файла по заданной позиции
std::string read(std::ifstream &file, std::ios::pos_type pos) {
    file.clear();
    std::string number;
    std::string address;

    // Перемещаем указатель файла к заданной позиции
    file.seekg(pos);

    // Считываем строки из файла, разделенные нулевым символом
    std::getline(file, number, '\0') && std::getline(file, address, '\0');

    // Объединяем считанные строки и возвращаем результат
    return number + " " + address;
}

int main(int argc, char **argv) {
    // Проверяем, что передан аргумент командной строки с именем файла
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    // Открываем файл для чтения в бинарном режиме
    std::ifstream file(argv[1], std::ios::in | std::ios::binary);

    // Проверяем, удалось ли открыть файл
    if (!file.is_open()) {
        std::cout << "Can't open file!" << std::endl;
        return 1;
    }

    // Создаем вектор для хранения таблицы смещений (пар чисел и позиций в файле)
    std::vector<std::pair<long, std::ios::pos_type>> offset_table;

    std::string number;
    std::string address;

    // Запоминаем начальную позицию в файле
    std::ios::pos_type pos = file.tellg();

    // Читаем числа и адреса из файла и заполняем таблицу смещений
    while (std::getline(file, number, '\0') && std::getline(file, address, '\0')) {
        offset_table.push_back(std::pair<long, std::ios::pos_type>{std::stol(number), pos});
        pos = file.tellg(); // Запоминаем текущую позицию
    }

    // Сортируем таблицу смещений по числовым значениям
    std::sort(offset_table.begin(), offset_table.end(), [](auto &left, auto &right) {
        return left.first < right.first;
    });

    long required_number;
    std::cout << "Number: ";
    std::cin >> required_number;

    // Ищем заданное число в таблице смещений
    pos = find(offset_table, required_number);

    // Выводим позицию в файле и соответствующую строку
    if (pos != -1) {
        std::cout << "pos: " << pos << std::endl;
        std::cout << read(file, pos) << std::endl;
    } else {
        std::cout << "Number not found." << std::endl;
    }

    return 0;
}
