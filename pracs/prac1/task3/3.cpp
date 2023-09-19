#include <iostream>
#include <fstream>

const int BIT_ARRAY_SIZE = 140000;
const int BITS_PER_ULL = 64;

int main() {
    // Инициализация битового массива нулями
    unsigned long long bits[BIT_ARRAY_SIZE] = {0};

    // Вывод размера битового массива в MiB
    std::cout << "Bit array size: " << (double)BIT_ARRAY_SIZE * sizeof(unsigned long long) / (1024 * 1024) << " MiB" << std::endl;

    // Имена входного и выходного файлов
    const char* file_in_name = "pracs/prac1/task3/input.txt";
    const char* file_out_name = "pracs/prac1/task3/output.txt";

    // Открытие входного файла для чтения
    std::ifstream fin(file_in_name);
    if (!fin.is_open()) {
        std::cout << "Can't open file " << file_in_name << std::endl;
        return -1;
    }

    int n;

    // Замер начального времени
    auto start_time = std::chrono::high_resolution_clock::now();

    while (fin >> n) {
        // Проверка, что числа находятся в заданном диапазоне
        if (!(n >= 1000000 && n <= 9999999)) {
            std::cout << "Numbers must be in range 1000000..9000000!";
            return -1;
        }
        // Установка соответствующего бита в битовом массиве
        bits[(n - 1000000) / BITS_PER_ULL] |= (1ULL << (n - 1000000) % BITS_PER_ULL);
    }

    // Открытие выходного файла для записи
    std::ofstream fout(file_out_name);
    if (!fout.is_open()) {
        std::cout << "Can't open file " << file_out_name << std::endl;
        return -1;
    }

    // Запись отсортированной последовательности в файл
    for (int x = 1000000; x <= 9000000; x++) {
        if (bits[(x - 1000000) / BITS_PER_ULL] & (1ULL << (x - 1000000) % BITS_PER_ULL)) {
            fout << x << std::endl;
        }
    }

    // Замер времени завершения операции
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Elapsed time:  " << elapsed_time.count() << " milliseconds." << std::endl;

    return 0;
}
