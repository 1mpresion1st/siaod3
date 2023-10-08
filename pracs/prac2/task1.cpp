#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <utility>

const auto STREETS = {"Гагарина", "Домодедовская", "Ладыгина", "Бухарестская", "Космонавтов",
                      "1905 года", "Славы", "Чехова", "Балканская", "Ломоносова"};

std::random_device rd;
std::mt19937 gen(rd());


int random(int start, int end) {
    std::uniform_int_distribution<> distr(start, end); // define the range
    return distr(gen);
}

int random(int end) {
    return random(0, end);
}

template <typename Iterator>
Iterator random_choice(Iterator begin, Iterator end) {
    auto len = std::distance(begin, end);
    std::advance(begin, random(len-1));
    return begin;
}

std::string random_phone_number() {
    std::stringstream number_stream;

    number_stream << 7;

    for (int i = 0; i < 10; i++) {
        number_stream << random(9);
    }

    return number_stream.str();
}

int main() {
    // open file for writing
    std::string output;
    int n;
    std::cout << "Output file: ";
    std::cin >> output;
    std::cout << "Number: ";
    std::cin >> n;

    std::ofstream file(output, std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Can't write to the file" << std::endl;
        return 1;
    }

    for (int i = 0; i < 1000; i++) {
        std::string number = random_phone_number();

        std::string address = "ул. " + std::string(*random_choice(STREETS.begin(), STREETS.end())) + " " +\
                             std::to_string(random(1, 100));

        file.write(number.c_str(), number.size()+1);
        file.write(address.c_str(), address.size()+1);
    }

    file.close();
}
