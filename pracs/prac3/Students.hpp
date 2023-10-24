#ifndef MIREA_SIAOD3_STUDENTS_HPP
#define MIREA_SIAOD3_STUDENTS_HPP

#include <memory>
#include <vector>
#include "Student.hpp"

class Students {
private:
    std::vector<std::pair<int, Student*>*> buckets; // Вектор корзин для хранения студентов
    int size; // Размер хеш-таблицы

    int hash(int key) const; // Функция хеширования для вычисления индекса корзины
    int hash2(int key) const; // Вторая функция хеширования (второй шаг) для разрешения коллизий

public:
    explicit Students(int size=255); // Конструктор класса, инициализирующий размер хеш-таблицы
    void insert(Student *student); // Метод для вставки студента в хеш-таблицу
    void remove(int recordBookId); // Метод для удаления студента по номеру зачетной книжки
    Student *get(int recordBookId); // Метод для получения студента по номеру зачетной книжки
};

#endif //MIREA_SIAOD3_STUDENTS_HPP
