#include "Students.hpp"

int Students::hash(int key) const {
    return key % size; // Функция хеширования для вычисления индекса корзины на основе ключа
}

int Students::hash2(int key) const {
    return 123 + key % size; // Вторая функция хеширования (второй шаг) для обработки коллизий
}

void Students::insert(Student *student) {
    int key_hash = hash(student->record_book_id); // Вычисление хеша ключа
    int i = 1;
    while (buckets[key_hash] != nullptr) { // Поиск пустой корзины для вставки
        key_hash += i * hash2(student->record_book_id); // Решение коллизий с помощью второй хеш-функции
        i++;
    }
    buckets[key_hash] = new std::pair{student->record_book_id, student}; // Вставка студента в корзину
}

void Students::remove(int recordBookId) {
    int key_hash = hash(recordBookId); // Вычисление хеша ключа для удаления
    int i = 1;
    while (key_hash < size && (buckets[key_hash] == nullptr || buckets[key_hash]->first != recordBookId)) {
        key_hash += i * hash2(recordBookId); // Поиск корзины с указанным ключом
        i++;
    }

    if (key_hash < size)
        buckets[key_hash] = nullptr; // Удаление элемента, установив указатель в корзине на nullptr
}

Student * Students::get(int recordBookId) {
    int key_hash = hash(recordBookId); // Вычисление хеша ключа для поиска
    int i = 1;
    while (key_hash < size && (buckets[key_hash] == nullptr || buckets[key_hash]->first != recordBookId)) {
        key_hash += i * hash2(recordBookId); // Поиск корзины с указанным ключом
        i++;
    }
    if (key_hash < size)
        return buckets[key_hash]->second; // Возврат студента из корзины по ключу
    else
        return nullptr; // Если студент не найден, вернуть nullptr
}

Students::Students(int size) : size(size), buckets(std::vector<std::pair<int, Student*>*>(size)) {
    // Конструктор класса Students, инициализирующий размер и создающий вектор корзин
}
