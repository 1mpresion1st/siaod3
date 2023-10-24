#include <iostream>
#include "Student.hpp" // Включаем заголовочный файл для класса Student
#include "Students.hpp" // Включаем заголовочный файл для класса Students

int main() {
    Students students; // Создаем объект класса Students для хранения студентов

    // Вставляем несколько студентов в контейнер students
    students.insert(new Student(10, 22, "Ivanov Ivan Ivanovich"));
    students.insert(new Student(265, 20, "Petrov Dmitry Igorev"));
    students.insert(new Student(32, 10, "Maximov Roman Ivanonich"));
    students.insert(new Student(775, 12, "Romanov Roman Romanovich"));
    students.insert(new Student(287, 10, "Dmitriev Petr Maximovich"));
    students.insert(new Student(75, 13, "Ivanov Ifore Dmitrievich"));

    // Меню опций для пользователя
    auto menu_items = {
            "Insert",
            "Get",
            "Remove",
            "Exit"
    };

    while (true) {
        int i = 1;
        // Выводим меню на экран
        for (auto &item: menu_items) {
            std::cout << i << ". " << item << std::endl;
            i++;
        }
        int option = 0;
        std::cout << "Option: ";
        std::cin >> option;

        if (option == 1) { // Вставить студента
            std::string name, surname, patronymic;
            int id, group;
            std::cout << "Surname: ";
            std::cin >> surname;
            std::cout << "Name: ";
            std::cin >> name;
            std::cout << "Patronymic: ";
            std::cin >> patronymic;
            std::cout << "Record book ID: ";
            std::cin >> id;
            std::cout << "Group: ";
            std::cin >> group;

            // Создаем нового студента и вставляем его в контейнер
            students.insert(new Student(id, group, surname + " " + name + " " + patronymic));
        } else if (option == 2) { // Получить информацию о студенте
            int id;
            std::cout << "Record book ID: ";
            std::cin >> id;
            Student *student = students.get(id);
            if (student == nullptr) {
                std::cout << "Student does not exist!" << std::endl;
            } else {
                // Выводим информацию о студенте
                std::cout << "Student: " << student->full_name << ", " << student->record_book_id << ", " <<
                          student->group_number << std::endl;
            }
        } else if (option == 3) {  // Удалить студента
            int id;
            std::cout << "Record book ID: ";
            std::cin >> id;
            students.remove(id);
        }
        if (option == 4) { // Выход из программы
            return 0;
        }
    }
}
