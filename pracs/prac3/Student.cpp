#include "Student.hpp"

Student::
Student::Student(int record_book_id, int group_number, std::string full_name):
    record_book_id(record_book_id),
    group_number(group_number),
    full_name(std::move(full_name))
{}
