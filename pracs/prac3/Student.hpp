#ifndef MIREA_SIAOD3_STUDENT_HPP
#define MIREA_SIAOD3_STUDENT_HPP
#include <string>
#include <utility>

struct Student {
    int record_book_id;
    int group_number;
    std::string full_name;

    Student(int record_book_id, int group_number, std::string full_name);
};


#endif //MIREA_SIAOD3_STUDENT_HPP
