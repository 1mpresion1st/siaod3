#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


std::ios::pos_type find(std::vector<std::pair<long, std::ios::pos_type>> &offset_table, long key) {
    int l = 0;
    int r = offset_table.size();
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (offset_table[m].first == key)
            return offset_table[m].second;
        if (offset_table[m].first < key)
            l = m + 1;
        r = m - 1;
    }
    return -1;
}

std::string read(std::ifstream &file, std::ios::pos_type pos) {
    file.clear();
    std::string number;
    std::string address;

    file.seekg(pos);
    std::getline(file, number, '\0') && std::getline(file, address, '\0');

    return number + " " + address;
}

int main(int argc, char **argv) {
    std::ifstream file(argv[1], std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Can't open file!" << std::endl;
        return 1;
    }

    std::vector<std::pair<long, std::ios::pos_type>> offset_table;
    std::string number;
    std::string address;

    std::ios::pos_type pos = file.tellg();
    while (std::getline(file, number, '\0') && std::getline(file, address, '\0')) {
        offset_table.push_back(std::pair<long, std::ios::pos_type>{std::stol(number), pos});
        pos = file.tellg();
    }

    std::sort(offset_table.begin(), offset_table.end(), [](auto &left, auto &right) {
        return left.first < right.first;
    });

    long required_number;
    std::cout << "Number: ";
    std::cin >> required_number;

    pos = find(offset_table, required_number);
    std::cout << "pos: " << pos << std::endl;
    std::cout << read(file, pos) << std::endl;

    return 0;
}
