#include <iostream>
#include <fstream>
#include <windows.h>


int main(int argc, char **argv) {
    SetConsoleOutputCP(CP_UTF8);
    // Выводим первый аргумент командной строки (путь к файлу) на экран.
    std::cout << argv[1] << std::endl;

    // Открываем файл, указанный в аргументах командной строки, для чтения в бинарном режиме.
    std::ifstream file(argv[1], std::ios::in | std::ios::binary);

    // Проверяем, удалось ли открыть файл. Если нет, выводим сообщение об ошибке и завершаем программу.
    if (!file.is_open()) {
        std::cout << "Can't open file!" << std::endl;
        return 1;
    }

    // Запрашиваем у пользователя ввод числа, которое мы будем искать в файле.
    std::string required_number;
    std::cout << "Number: ";
    std::cin >> required_number;

    // Создаем переменные для хранения считанных чисел и адресов.
    std::string number;
    std::string address;

    // Читаем данные из файла поочередно, считывая число и адрес чередующимися '\0' символами.
    while (std::getline(file, number, '\0') && std::getline(file, address, '\0')) {
        // Если считанное число совпадает с запрошенным числом, выводим его и соответствующий адрес.
        if (number == required_number) {
            std::cout << number << " " << address;
            return 0;
        }
    }

    // Если заданное число не было найдено в файле, выводим сообщение об отсутствии.
    std::cout << "Not found" << std::endl;

    // Завершаем программу с кодом возврата 0 (успешное завершение).
    return 0;
}