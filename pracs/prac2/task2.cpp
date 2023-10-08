#include <iostream>
#include <fstream>

int main(int argc, char **argv) {
    std::cout << argv[1] << std::endl;

    std::ifstream file(argv[1], std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Can't open file!" << std::endl;
        return 1;
    }

    std::string required_number;
    std::cout << "Number: ";
    std::cin >> required_number;

    std::string number;
    std::string address;

    while (std::getline(file, number, '\0') && std::getline(file, address, '\0')) {
        if (number == required_number) {
            std::cout << number << " " << address;
            return 0;
        }
    }
    std::cout << "Not found" << std::endl;
}
